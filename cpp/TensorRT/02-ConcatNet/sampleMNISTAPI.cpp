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

const std::string gSampleName = "TensorRT.sample_mnist_api";

struct SampleMNISTAPIParams : public samplesCommon::SampleParams
{
    int inputH;                  //!< The input height
    int inputW;                  //!< The input width
    int outputSize;              //!< The output size
    std::string weightsFile;     //!< The filename of the weights file
    std::string mnistMeansProto; //!< The proto file containing means
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

private:
    SampleMNISTAPIParams mParams; //!< The parameters for the sample.
    int mNumber{0}; //!< The number to classify
    std::shared_ptr<nvinfer1::ICudaEngine> mEngine; //!< The TensorRT engine used to run the network
    bool constructNetwork(SampleUniquePtr<nvinfer1::IBuilder>& builder,
        SampleUniquePtr<nvinfer1::INetworkDefinition>& network, SampleUniquePtr<nvinfer1::IBuilderConfig>& config);
    bool processInput(const samplesCommon::BufferManager& buffers);
    bool verifyOutput(const samplesCommon::BufferManager& buffers);
    std::map<std::string, nvinfer1::Weights> loadWeights(const std::string& file);
};


bool SampleMNISTAPI::build()
{

    auto builder = SampleUniquePtr<nvinfer1::IBuilder>(nvinfer1::createInferBuilder(sample::gLogger.getTRTLogger()));
    if (!builder) return false;

    auto network = SampleUniquePtr<nvinfer1::INetworkDefinition>(builder->createNetwork());
    if (!network) return false;

    auto config = SampleUniquePtr<nvinfer1::IBuilderConfig>(builder->createBuilderConfig());
    if (!config) return false;

    auto constructed = constructNetwork(builder, network, config);
    if (!constructed) return false;

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
    // Create input tensor
    ITensor* tensor1 = network->addInput(
        mParams.inputTensorNames[0].c_str(), DataType::kFLOAT, Dims3{1, mParams.inputH, mParams.inputW});
    assert(tensor1);

    ITensor* tensor2 = network->addInput(
        mParams.inputTensorNames[1].c_str(), DataType::kFLOAT, Dims3{1, mParams.inputH, mParams.inputW});
    assert(tensor2);

    ITensor* tensors[] = {tensor1, tensor2};

    IConcatenationLayer* concat_layer = network->addConcatenation(
        tensors, 2);
    assert(concat_layer);
    concat_layer->setAxis(1);

    concat_layer->getOutput(0)->setName(mParams.outputTensorNames[0].c_str());
    network->markOutput(*concat_layer->getOutput(0));

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
    // Create RAII buffer manager object
    samplesCommon::BufferManager buffers(mEngine, mParams.batchSize);

    auto context = SampleUniquePtr<nvinfer1::IExecutionContext>(mEngine->createExecutionContext());
    if (!context) return false;

    // Read the input data into the managed buffers
    assert(mParams.inputTensorNames.size() == 2);
    if (!processInput(buffers)) return false;

    // Memcpy from host input buffers to device input buffers
    buffers.copyInputToDevice();

    bool status = context->execute(mParams.batchSize, buffers.getDeviceBindings().data());
    if (!status) return false;

    // Memcpy from device output buffers to host output buffers
    buffers.copyOutputToHost();

    // Verify results
    if (!verifyOutput(buffers))return false;

    return true;
}


bool SampleMNISTAPI::processInput(const samplesCommon::BufferManager& buffers)
{
    std::vector<float> fileDataOnes(mParams.inputH * mParams.inputW, 1.0f);
    std::vector<float> fileDataTwos(mParams.inputH * mParams.inputW, 2.0f);

    // Print ASCII representation of digit image
    std::cout << "\nInput 1:\n" << std::endl;

    //for (int i = 0; i < mParams.inputH * mParams.inputW; i++) std::cout << fileData[i] << std::endl;
    for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
    {
        std::cout << fileDataOnes[i] << (((i + 1) % mParams.inputW) ? "" : "\n");
    }

    std::cout << "\nInput 2:\n" << std::endl;
    for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
    {
        std::cout << fileDataTwos[i] << (((i + 1) % mParams.inputW) ? "" : "\n");
    }

    // Parse mean file
    auto parser = SampleUniquePtr<nvcaffeparser1::ICaffeParser>(nvcaffeparser1::createCaffeParser());
    if (!parser) return false;

    auto meanBlob = SampleUniquePtr<nvcaffeparser1::IBinaryProtoBlob>(
        parser->parseBinaryProto(locateFile(mParams.mnistMeansProto, mParams.dataDirs).c_str()));
    if (!meanBlob) return false;

    
    float* hostDataBuffer1 = static_cast<float*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
    float* hostDataBuffer2 = static_cast<float*>(buffers.getHostBuffer(mParams.inputTensorNames[1]));
    for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
    {
        hostDataBuffer1[i] = float(fileDataOnes[i]);
    }
    for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
    {
        hostDataBuffer2[i] = float(fileDataTwos[i]);
    }

    return true;
}


bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
{
    float* prob = static_cast<float*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
    std::cout << "\nOutput:\n" << std::endl;

    for (int i = 0; i < mParams.inputH * mParams.inputW *2 ; i++) std::cout << prob[i] << std::endl;
    for (int i = 0; i < mParams.inputH * mParams.inputW * 2; i++)
    {
        std::cout << prob[i] << (((i + 1) % mParams.inputW) ? "" : "\n");
    }
}


SampleMNISTAPIParams initializeSampleParams(const samplesCommon::Args& args)
{
    SampleMNISTAPIParams params;
    if (args.dataDirs.empty()) //!< Use default directories if user hasn't provided directory paths
    {
        params.dataDirs.push_back("data/mnist/");
        params.dataDirs.push_back("data/samples/mnist/");
    }
    else //!< Use the data directory provided by the user
    {
        params.dataDirs = args.dataDirs;
    }
    params.inputTensorNames.push_back("tensor1");
    params.inputTensorNames.push_back("tensor2");
    params.batchSize = 1;
    params.outputTensorNames.push_back("concat_layer");
    params.dlaCore = args.useDLACore;
    params.int8 = args.runInInt8;
    params.fp16 = args.runInFp16;

    params.inputH = 3;
    params.inputW = 3;
    params.outputSize = 1;
    params.weightsFile = "mnistapi.wts";
    params.mnistMeansProto = "mnist_mean.binaryproto";

    return params;
}


void printHelpInfo() {}

int main(int argc, char** argv)
{
    samplesCommon::Args args;
    bool argsOK = samplesCommon::parseArgs(args, argc, argv);
    if (!argsOK)
    {
        sample::gLogError << "Invalid arguments" << std::endl;
        printHelpInfo();
        return EXIT_FAILURE;
    }
    if (args.help)
    {
        printHelpInfo();
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
