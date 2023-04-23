RAW_CPP_TXT = \
"""
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

#include <cuda_fp16.h>
#include <cstdint>

#define IN_TYPE_A $IN_TYPE_A$
#define IN_TYPE_B $IN_TYPE_B$
#define OUT_TYPE $OUT_TYPE$

#define IN_VALUE_TYPE_A $IN_VALUE_TYPE_A$
#define IN_VALUE_TYPE_B $IN_VALUE_TYPE_B$
#define OUT_VALUE_TYPE $OUT_VALUE_TYPE$

std::string log_file_name = "$LOG_FILENAME$";
int DATA_SIZE = 4;


template<typename T>
bool writeVectorToFile(const std::vector<T>&, const std::string&);

const std::string gSampleName = "TensorRT.sample_mnist_api";

struct SampleMNISTAPIParams : public samplesCommon::SampleParams
{
    int input1_H;                  //!< The input height
    int input1_W;                  //!< The input width

    int input2_H;
    int input2_W;

    int concatDim;               // [b, H, W] 

    int outputSize;              //!< The output size

    DataType inTypeA = IN_TYPE_A;
    DataType inTypeB = IN_TYPE_B;
    DataType outType = OUT_TYPE;
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
    ITensor* tensor1 = network->addInput(
        mParams.inputTensorNames[0].c_str(), mParams.inTypeA, Dims3{1, mParams.input1_H, mParams.input1_W});
    assert(tensor1);

    ITensor* tensor2 = network->addInput(
        mParams.inputTensorNames[1].c_str(), mParams.inTypeB, Dims3{1, mParams.input2_H, mParams.input2_W});
    assert(tensor2);

    ITensor* tensors[] = {tensor1, tensor2};

    IElementWiseLayer* opLayer = network->addElementWise(*tensor1, *tensor2, ElementWiseOperation::kGREATER);
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
    $INIT_INPUT_DATA_A$
    $INIT_INPUT_DATA_B$

    std::cout << "\\nInput A:\\n" << std::endl;
    for (int i = 0; i < DATA_SIZE; i++)
    {
        std::cout << static_cast<float>(DataA[i]) << "\\n";
    }

    std::cout << "\\nInput B:\\n" << std::endl;
    for (int i = 0; i < DATA_SIZE; i++)
    {
        std::cout << static_cast<float>(DataB[i]) << "\\n";
    }

    IN_VALUE_TYPE_A* hostDataBuffer1 = static_cast<IN_VALUE_TYPE_A*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
    IN_VALUE_TYPE_B* hostDataBuffer2 = static_cast<IN_VALUE_TYPE_B*>(buffers.getHostBuffer(mParams.inputTensorNames[1]));
    for (int i = 0; i < DATA_SIZE;i++)
    {
        hostDataBuffer1[i] = IN_VALUE_TYPE_A(DataA[i]);
    }
    for (int i = 0; i < DATA_SIZE; i++)
    {
        hostDataBuffer2[i] = IN_VALUE_TYPE_B(DataB[i]);
    }

    return true;
}


bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
{
    OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));

    std::vector<OUT_VALUE_TYPE> output(prob, prob + DATA_SIZE);
    std::cout << "\\nOutput:\\n" << std::endl;
    for (int i = 0; i < DATA_SIZE; i++) 
    {
        std::cout << static_cast<float>(output[i]) << std::endl;
    }

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

    params.inputTensorNames.push_back("tensor1");
    params.inputTensorNames.push_back("tensor2");
    params.batchSize = 1;
    params.outputTensorNames.push_back("identityLayer");
    params.dlaCore = args.useDLACore;
    params.int8 = args.runInInt8;
    params.fp16 = args.runInFp16;

    params.input1_H = 2;
    params.input1_W = 2;
    params.input2_H = 2;
    params.input2_W = 2;
    params.concatDim = 2;
    params.outputSize = 1;

    return params;
}


template<typename T>
bool writeVectorToFile(const std::vector<T>& v, const std::string& file_path) {
    std::ofstream out_file(file_path);
    if (!out_file.is_open()) {
        std::cout << "fail to open log file ." << std::endl;
        return false;
    }
    for (const auto& item : v) {
        out_file << item << std::endl;
    }
    out_file.close();
    return true;
}

int main(int argc, char** argv)
{
    std::cout << log_file_name << std::endl;
    samplesCommon::Args args;
    args.runInFp16 = true;
    args.runInInt8 = true;
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

    sample::gLogInfo << "Building and running a GPU inference engine for EWLossTest" << std::endl;

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

"""

OUTPUT_PATH = "./ewlosstest.cpp"

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-a", "--intypeA", default="")
parser.add_argument("-b", "--intypeB", default="")
parser.add_argument("-o", "--outtype", default="")
parser.add_argument("-d", "--data", default="")
args = parser.parse_args()

inTypeA = args.intypeA
inTypeB = args.intypeB
outType = args.outtype
data = args.data

typeSet = ["f", "h", "i8", "i32", "b"]
typeSet_FN = ["float", "half", "int8_t", "int32_t", "bool"]
typeSet_TRT = ["DataType::kFLOAT", "DataType::kHALF", "DataType::kINT8", "DataType::kINT32", "DataType::kBOOL"]

assert inTypeA in typeSet
assert inTypeB in typeSet
assert outType in typeSet

code_IN_TYPE_A = typeSet_TRT[typeSet.index(inTypeA)]
code_IN_VALUE_TYPE_A = typeSet_FN[typeSet.index(inTypeA)]

code_IN_TYPE_B = typeSet_TRT[typeSet.index(inTypeB)]
code_IN_VALUE_TYPE_B = typeSet_FN[typeSet.index(inTypeB)]

code_OUT_TYPE = typeSet_TRT[typeSet.index(outType)]
code_OUT_VALUE_TYPE = typeSet_FN[typeSet.index(outType)]

code_LOG_FILENAME = f"./logs/{inTypeA}_{inTypeB}_{outType}_{data}_kgreater.txt"

code_INIT_INPUT_DATA_A = ""
if data[0] == "f":
    code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = {0.0f, 0.5f, 1.0f, 1.5f};"
if data[0] == "i":
    code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = { 1, 2, 3, 4};"
if data[0] == "b":
    code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = {true, false, true, false};"

code_INIT_INPUT_DATA_B = ""
if data[1] == "f":
    code_INIT_INPUT_DATA_B = "std::vector<IN_VALUE_TYPE_B> DataB = {0.0f, 0.5f, 1.0f, 1.5f};"
if data[1] == "i":
    code_INIT_INPUT_DATA_B = "std::vector<IN_VALUE_TYPE_B> DataB = { 1, 2, 3, 4};"
if data[1] == "b":
    code_INIT_INPUT_DATA_B = "std::vector<IN_VALUE_TYPE_B> DataB = {true, false, true, false};"

TGT_CPP_TXT = RAW_CPP_TXT\
    .replace("$LOG_FILENAME$", code_LOG_FILENAME)\
    .replace("$IN_TYPE_A$", code_IN_TYPE_A)\
    .replace("$IN_VALUE_TYPE_A$", code_IN_VALUE_TYPE_A)\
    .replace("$IN_TYPE_B$", code_IN_TYPE_B)\
    .replace("$IN_VALUE_TYPE_B$", code_IN_VALUE_TYPE_B)\
    .replace("$OUT_TYPE$", code_OUT_TYPE)\
    .replace("$OUT_VALUE_TYPE$", code_OUT_VALUE_TYPE)\
    .replace("$INIT_INPUT_DATA_A$", code_INIT_INPUT_DATA_A)\
    .replace("$INIT_INPUT_DATA_B$", code_INIT_INPUT_DATA_B)

with open("./ewlosstest.cpp", "w") as f:
    f.write(TGT_CPP_TXT)

print("OK")
