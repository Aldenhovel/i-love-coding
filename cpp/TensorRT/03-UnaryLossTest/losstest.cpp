
#include "argsParser.h"
#include "buffers.h"
#include "common.h"
#include "logger.h"

#include "NvCaffeParser.h"
#include "NvInfer.h"
#include <cuda_runtime_api.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <fstream>
#include <cuda_fp16.h> // kHALF --> half
#include <cstdint>
#include <bitset>

#define OP UnaryOperation::kSQRT

std::string log_file_name = "./logs/f_b_kSQRT.txt";
#define IN_TYPE DataType::kFLOAT
#define IN_VALUE_TYPE float

#define OUT_TYPE DataType::kBOOL
#define OUT_VALUE_TYPE bool

int DATA_SIZE = 5;



template <typename T>
bool writeVectorToFile(const std::vector<T>& v, const std::string& file_path);


const std::string gSampleName = "TensorRT.sample_mnist_api";


struct SampleMNISTAPIParams : public samplesCommon::SampleParams
{
    int inputH;                  //!< The input height
    int inputW;                  //!< The input width
    int outputSize;              //!< The output size

    UnaryOperation op = OP; //UnaryOperation::kEXP;
    DataType inType = IN_TYPE; //DataType::kFLOAT;
    DataType outType = OUT_TYPE; //DataType::kFLOAT;

};


class SampleMNISTAPI
{
    template <typename T>
    using SampleUniquePtr = std::unique_ptr<T, samplesCommon::InferDeleter>;

public:
    SampleMNISTAPI(const SampleMNISTAPIParams& params)
        : mParams(params)
        , mEngine(nullptr)
    {
    }

    bool build();
    bool infer();
    bool teardown();

private:
    SampleMNISTAPIParams mParams; //!< The parameters for the sample.

    int mNumber{0}; //!< The number to classify

    std::shared_ptr<nvinfer1::ICudaEngine> mEngine; //!< The TensorRT engine used to run the network

    bool constructNetwork(SampleUniquePtr<nvinfer1::IBuilder>& builder,
        SampleUniquePtr<nvinfer1::INetworkDefinition>& network, SampleUniquePtr<nvinfer1::IBuilderConfig>& config);
    bool processInput(const samplesCommon::BufferManager& buffers);
    bool verifyOutput(const samplesCommon::BufferManager& buffers);

};

bool SampleMNISTAPI::build()
{
    auto builder = SampleUniquePtr<nvinfer1::IBuilder>(nvinfer1::createInferBuilder(sample::gLogger.getTRTLogger()));
    if (!builder)
    {
        return false;
    }

    auto network = SampleUniquePtr<nvinfer1::INetworkDefinition>(builder->createNetwork());
    if (!network)
    {
        return false;
    }

    auto config = SampleUniquePtr<nvinfer1::IBuilderConfig>(builder->createBuilderConfig());
    if (!config)
    {
        return false;
    }

    auto constructed = constructNetwork(builder, network, config);
    if (!constructed)
    {
        return false;
    }

    assert(network->getNbInputs() == 1);
    auto inputDims = network->getInput(0)->getDimensions();
    assert(inputDims.nbDims == 3);

    assert(network->getNbOutputs() == 1);
    auto outputDims = network->getOutput(0)->getDimensions();
    assert(outputDims.nbDims == 3);

    return true;
}

bool SampleMNISTAPI::constructNetwork(SampleUniquePtr<nvinfer1::IBuilder>& builder,
    SampleUniquePtr<nvinfer1::INetworkDefinition>& network, SampleUniquePtr<nvinfer1::IBuilderConfig>& config)
{
    ITensor* data = network->addInput(
        mParams.inputTensorNames[0].c_str(), mParams.inType, Dims3{1, mParams.inputH, mParams.inputW});
    assert(data);

    IUnaryLayer* opLayer = network->addUnary(*data, mParams.op);
    //opLayer->getOutput(0)->setType(mParams.outType);
    assert(opLayer);

    IIdentityLayer* identityLayer = network->addIdentity(*opLayer->getOutput(0));
    identityLayer->setOutputType(0, mParams.outType);
    identityLayer->getOutput(0)->setType(mParams.outType);
    assert(identityLayer);

    identityLayer->getOutput(0)->setName(mParams.outputTensorNames[0].c_str());
    network->markOutput(*identityLayer->getOutput(0));

    // Build engine
    builder->setMaxBatchSize(mParams.batchSize);
    config->setMaxWorkspaceSize(16_MiB);
    if (mParams.fp16)
    {
        config->setFlag(BuilderFlag::kFP16);
    }
    if (mParams.int8)
    {
        config->setFlag(BuilderFlag::kINT8);
        samplesCommon::setAllTensorScales(network.get(), 64.0f, 64.0f);
    }

    samplesCommon::enableDLA(builder.get(), config.get(), mParams.dlaCore);

    mEngine = std::shared_ptr<nvinfer1::ICudaEngine>(
        builder->buildEngineWithConfig(*network, *config), samplesCommon::InferDeleter());
    if (!mEngine)
    {
        return false;
    }

    return true;
}

bool SampleMNISTAPI::infer()
{
    samplesCommon::BufferManager buffers(mEngine, mParams.batchSize);

    auto context = SampleUniquePtr<nvinfer1::IExecutionContext>(mEngine->createExecutionContext());
    if (!context)
    {
        return false;
    }

    assert(mParams.inputTensorNames.size() == 1);
    if (!processInput(buffers))
    {
        return false;
    }
    buffers.copyInputToDevice();

    bool status = context->execute(mParams.batchSize, buffers.getDeviceBindings().data());
    if (!status)
    {
        return false;
    }

    buffers.copyOutputToHost();

    if (!verifyOutput(buffers))
    {
        return false;
    }

    return true;
}

bool SampleMNISTAPI::processInput(const samplesCommon::BufferManager& buffers)
{
    srand(unsigned(time(nullptr)));

    std::vector<IN_VALUE_TYPE> data = {0.0f, 0.5f, 1.0f, 1.5f, 2.0f};


    std::cout << "\nInput:\n" << std::endl;
    for (int i = 0; i < DATA_SIZE; i++) std::cout << static_cast<float>(data[i]) << std::endl;
    
    IN_VALUE_TYPE* hostDataBuffer = static_cast<IN_VALUE_TYPE*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
    for (int i = 0; i < DATA_SIZE; i++)
    {
        hostDataBuffer[i] = IN_VALUE_TYPE(data[i]);
    }

    return true;
}


bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
{
    OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
    std::cout << "\nOutput:\n" << std::endl;

    std::vector<OUT_VALUE_TYPE> output(prob, prob + DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++) std::cout << static_cast<float>(prob[i]) << std::endl;

    if (!writeVectorToFile(output, log_file_name))
    {
        std::cout << "fail to write log ." << std::endl;
        return false;
    };
    std::cout << "Done" << std::endl;
    return true;
}


SampleMNISTAPIParams initializeSampleParams(const samplesCommon::Args& args)
{
    SampleMNISTAPIParams params;
    if (args.dataDirs.empty()) //!< Use default directories if user hasn't provided directory paths
    {
    }
    else //!< Use the data directory provided by the user
    {
        params.dataDirs = args.dataDirs;
    }
    params.inputTensorNames.push_back("data");
    params.batchSize = 1;
    params.outputTensorNames.push_back("prob");
    params.dlaCore = args.useDLACore;
    params.int8 = args.runInInt8;
    params.fp16 = args.runInFp16;

    params.inputH = 3;
    params.inputW = 3;
    params.outputSize = 1;
    return params;
}

template<typename T>
bool writeVectorToFile(const std::vector<T>& v, const std::string& file_path) {

    std:: cout << file_path << std::endl;
    std::ofstream out_file(file_path); // 打开输出文件流
    if (!out_file.is_open()) { // 打开失败则返回 false
        std::cout << "fail to open log file ." << std::endl;
        return false;
    }

    for (const auto& item : v) { // 遍历 vector 中的每个元素
        out_file << static_cast<float>(item) << std::endl; // 将每个元素写入文件中并换行
    }

    out_file.close(); // 关闭输出文件流
    return true;
}



int main(int argc, char** argv)
{
    samplesCommon::Args args; 
    args.runInInt8 = true;
    args.runInFp16 = true;
    bool argsOK = samplesCommon::parseArgs(args, argc, argv);
    if (!argsOK)
    {
        sample::gLogError << "Invalid arguments" << std::endl;
        return EXIT_FAILURE;
    }
    if (args.help)
    {
        return EXIT_SUCCESS;
    }

    auto sampleTest = sample::gLogger.defineTest(gSampleName, argc, argv);

    sample::gLogger.reportTestStart(sampleTest);

    SampleMNISTAPI sample(initializeSampleParams(args));

    sample::gLogInfo << "Building and running a GPU inference engine for MNIST API" << std::endl;

    if (!sample.build())
    {
        return sample::gLogger.reportFail(sampleTest);
    }
    if (!sample.infer())
    {
        return sample::gLogger.reportFail(sampleTest);
    }

    return sample::gLogger.reportPass(sampleTest);
}

