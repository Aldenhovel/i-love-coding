# UnaryLossTest

## 目标

1. 对一个简单的 `UnaryOperation` 算子网络计算在 `kFLOAT` `kHALF` `kINT8` `kINT32` `kBOOL` 分别作为输入和输出的类型时，与标准输入输出（以 `kFLOAT-kFLOAT` 为标准）的精度误差。
2. 网络需要指定输出输出类型，以及在过程中通过 `IIdentityLayer` 强制精度转化，具体流程是：
   - 确定输入输出精度对，例如 `float - kFLOAT` 。
   - 生产输入数据，如 `vector<float> data{ 1.0f, 2.0f }` 并使用 `static_cast<float>` 转化为浮点打印出来。
   - 将网络 `network->addInput` 设置为输入精度，如 `DataType::kFLOAT` 。
   - 进行 `UnaryOperation` 运算。
   - 使用 `IIdentityLayer` 的 `->setOutputType` `->setType` 进行强制精度转换，并标记为输出。
   - 将获得的 `void*` 指针使用 `static_cast<>` 转换为对应类型，如 `DataType::kHALF` 转化为 `half*` 类型。
   - 将 `half*` 指针的内容转化为 `vector<half>` ，并且输出时使用 `static_cast<float>` 打印，并且保存在 log 文件。
   - 使用 Python 脚本计算测试样本和标准样本的误差， $MSE Loss$ 保存记录。 

## 分离 C++ 项目

之前的所有修改网络都是基于 `sampleMNISTAPI` 之下的，现在我们在 `TensorRT/samples/opensource/` 下新建一个项目 `LossTest` ，后面测试和其他操作都在这个项目下做。

1. 仿照 `sampleMNISTAPI` 的目录结构创建 `LossTest` :

   ```bash
   cd ~/trainee/TensorRT
   export TRT_SOURCE=`pwd`
   cd $TRT_SOURCE/samples/opensource/
   mkdir LossTest && cd LossTest
   touch losstest.cpp
   touch CMakeLists.txt
   ```

2. 将 `sampleMNISTAPI.cpp` 的内容进行大量精简

   ```cpp
   ......
   ```

   复制进去 `losstest.cpp` 作为后面修改的骨干代码。

3. 编辑 `CMakeLists.txt` 使他必须包含 `losstest.cpp` :

   ```cmake
   SET(SAMPLE_SOURCES
       losstest.cpp
   )
   set(SAMPLE_PARSERS "caffe")
   include(../../CMakeSamplesTemplate.txt)
   ```

4. 返回 `$TRT_SOURCE/build` 对项目进行重新编译：

   ```bash
   cd $TRT_SOURCE/build
   cmake ..
   make -j(nproc)
   ```

5. 回到 `out/` 发现已经将 `LossTest` 编译成功，验证：

   ```bash
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/xavier/trainee/TensorRT/build/out
   ./loss_test
   ```

   成功运行即可。

## 修改网络 `DataType`

1. 在构建网络时需要对 `Input` 和 `Output` 做数据类型指定，原来的程序针对 in / out 为 `kFLOAT / kFLOAT` ，现在为了替换需要，将网络的元操作 `op` ，输入 / 输出数据类型 `inType / outType` 在初始化 `mParams` 时指定：

   ```cpp
   struct SampleMNISTAPIParams : public samplesCommon::SampleParams
   {
       int inputH;                  //!< The input height
       int inputW;                  //!< The input width
       int outputSize;              //!< The output size
   
       UnaryOperation op = UnaryOperation::kEXP;	// 元操作
       DataType inType = DataType::kFLOAT;			// 输入数据类型，对应 addInput()
       DataType outType = DataType::kHALF;			// 输出数据类型，对应 network->markOutput(x) 的 x
   
   };
   ```

2. 修改 `constructNetwork()` 使其按照 `mParams` 的数据类型生成网络：

   ```cpp
   bool SampleMNISTAPI::constructNetwork(SampleUniquePtr<nvinfer1::IBuilder>& builder,
       SampleUniquePtr<nvinfer1::INetworkDefinition>& network, SampleUniquePtr<nvinfer1::IBuilderConfig>& config)
   {
       ITensor* data = network->addInput(
           mParams.inputTensorNames[0].c_str(), mParams.inType, Dims3{1, mParams.inputH, mParams.inputW});
       assert(data);
   
       IUnaryLayer* opLayer = network->addUnary(*data, mParams.op);
       assert(opLayer);
       
       // 这里使用 IIdentityLayer 实现可靠的 float half int8_t int32_t bool 转化
       IIdentityLayer* identityLayer = network->addIdentity(*opLayer->getOutput(0));
       identityLayer->setOutputType(0, mParams.outType);
       identityLayer->getOutput(0)->setType(mParams.outType);
       assert(identityLayer);
   
       opLayer->getOutput(0)->setName(mParams.outputTensorNames[0].c_str());
       network->markOutput(*opLayer->getOutput(0));
   
       // Build engine part 不动
       // ......
   
       return true;
   }
   ```

## 进一步修改 `DataType` 及打印预览

1. 原网络中对应网络 `kFLOAT / kFLOAT` 的输入输出，使得 `processInput()` `verifyOutput()`  都是以 `vector<float>` `float*` 为输入输出的，因为网络层的数据精度变化了，输入和输出数据类型也要随之改变，否则可能会内存泄漏。

2. 使用宏修改 `processInput()` 中的产生数据和 `verifyOutput()` 产生的数据，最后要使用 `static_cast<float>` 转化才能正常输出：

   ```cpp
   #define OP UnaryOperation::kEXP
   #define IN_TYPE DataType::kFLOAT // kHALF, kINT8, kINT32, kBOOL
   #define IN_VALUE_TYPE float      // half, int8_t, int32_t, bool
   #define OUT_TYPE DataType::kINT8 // kHALF, kINT8, kINT32, kBOOL
   #define OUT_VALUE_TYPE int8_t    // half, int8_t, int32_t, bool
   
   // struct SampleMNISTAPIParams
   UnaryOperation op = OP;
   DataType inType = IN_TYPE;
   DataType outType = OUT_TYPE;
   
   // processInput
   // 根据 IN_TYPE 类型不同需要生成不同的测试数值
   // 测试 kFLAOT, kHALF 使用 vector<IN_TYPE> {float ... }
   // 测试 kINT8, kINT32 使用 vector<IN_TYPE> {unsigned int ... }
   // 测试 kBOOL 使用 vector<INTYPE> {bool ... }
   std::vector<IN_VALUE_TYPE> data = { 1, 2, 3, 4, 5};
   std::vector<IN_VALUE_TYPE> data = {0.0f, 0.5f, 1.0f, 1.5f, 2.0f};
   std::vector<IN_VALUE_TYPE> data = {true, false, true, false, true};
   
   // 以 float 形式展示
   std::cout << "\nInput:\n" << std::endl;
   for (int i = 0; i < 5; i++) std::cout << static_cast<float>(data[i]) << std::endl;
   // 将 data 装载到 hostDataBuffer
   IN_VALUE_TYPE* hostDataBuffer = static_cast<IN_VALUE_TYPE*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
   for (int i = 0; i < 5; i++)
   {
       hostDataBuffer[i] = IN_VALUE_TYPE(data[i]);
   }
   
   // verifyOutput
   // 以 OUT_TYPE 类型获取输出结果 prob ，拷贝到 vector 中
   OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
   std::vector<OUT_VALUE_TYPE> output(prob, prob +5);
   // 以 float 形式输出结果
   for (int i = 0; i < 5; i++) std::cout << static_cast<float>(prob[i]) << std::endl;
   ```

   - `DataType::kFLOAT` $\rightarrow$ `float`

   - `DataType::kHALF` $\rightarrow$ `half` 需要 `#include <cuda_fp16.h>` 后使用。

     需要将在 `args` 中开启 `fp16`：

     ```cpp
     // main
     args.runInFP16 = true;
     ```

   - `DataType::kINT8` $\rightarrow$ `int8_t` 需要 `#include <cstdint>` 后使用。

     需要将在 `args` 中开启 `int8`：

     ```cpp
     // main
     args.runInInt8 = true;
     ```

   - `DataType::kINT32` $\rightarrow$ `int32_t` 需要 `#include <cstdint>` 后使用。

   - `DataType::kBOOL` $\rightarrow$ `bool`

## 在 `verifyOutput` 中写入 log 文件

1. 设计将 `loss_test` 里面测试的结果 `vector` 写入 `logs/{inType}_{outType}_{op}.txt` 中，等全部测试完了再使用 log 文件计算损失。

2. 日志写入函数：

   ```cpp
   template<typename T>
   bool writeVectorToFile(const std::vector<T>& v, const std::string& file_path) {
       std:: cout << file_path << std::endl;
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
   ```

3. 在 `verifyOutput` 中使用 `writeVectorToFile()` ：

   ```cpp
   // verifyOutput
   std::string log_file_name = "./logs/float_half_kEXP.txt";
   
   OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
   std::vector<OUT_VALUE_TYPE> output(prob, prob +8);
   
   if (!writeVectorToFile(output, log_file_name))
   {
   	std::cout << "fail to write log ." << std::endl;
   	return false;
   };
   ```

## 脚本检验 Loss

1. 当前 `build/out/logs` 下已经得到 `{inType}_{outType}_{op}.txt` 的日志文件，假设要计算 `inType=kHALF` `outType=kFLOAT` 的损失，需要的是 ：

   - `float_float_kEXP.txt` 作为真实值。
   - `half_float_kEXP.txt` 作为预测值。

   为了简约，`inType` `outType` 类型名设定为 `float` `half` `int8` `int32` `bool` ，`op` 名与 TensorRT 一致。

2. 使用 `calc_loss.py` 计算损失并格式化输出：

   ```python
   import argparse
   
   parser = argparse.ArgumentParser()
   parser.add_argument("-i", "--intype", default="")
   parser.add_argument("-o", "--outtype", default="")
   parser.add_argument("-x", "--option", default="")
   
   args = parser.parse_args()
   
   ca_in = args.intype
   ca_out = args.outtype
   op = args.option
   
   
   gt_file = f"./float_float_{op}.txt"
   ca_file = f"./{ca_in}_{ca_out}_{op}.txt"
   
   
   def read_txt_file(file_path):
       with open(file_path) as file:
           data = file.readlines()
           data = [line.rstrip('\n') for line in data]
       return data
   
   
   gt_values = read_txt_file(gt_file)
   ca_values = read_txt_file(ca_file)
   print("\n")
   print(f"in: {ca_in} ---- out: {ca_out} ---- op: {op}")
   print("\n")
   print("GroundTruth:\toutput:{" + " / ".join(gt_values) + "}")
   print("Candidate:\toutput:{" + " / ".join(ca_values) + "}")
   
   assert len(gt_values) == len(ca_values)
   loss, loss_pct = [], []
   for ix, (gt_v, ca_v) in enumerate(zip(gt_values, ca_values)):
       gt_v = float(gt_v)
       ca_v = float(ca_v)
       if gt_v <= 100 and gt_v >=-100 and ca_v>=-100 and ca_v <= 100:
           loss.append(abs(gt_v - ca_v))
   
   
   mse = sum([*map(lambda x: round(x**2, 10), loss)]) / len(loss)
   loss = [*map(lambda x: str(round(x, 6)), loss)]
   print("PrecisionLoss:\t" + " / ".join(loss) + f", mse={str(mse)}")
   print("MeanSqureError:\t" + str(mse))
   print("\n\n")
   ```

   ```bash
   python calc_loss.py -i int8 -o half -x kEXP
   ```

   ```
   in: int8 ---- out: half ---- op: kEXP
   
   GroundTruth:    output:{2.71828 / 7.38906 / 20.0855 / 54.5981 / 148.413}
   Candidate:      output:{1.65527 / 2.74023 / 4.53516 / 7.50391 / 12.4219}
   PrecisionLoss:  1.06301 / 4.64883 / 15.55034 / 47.09419, mse=620.604354125175
   MeanSqureError: 620.604354125175
   ```

## 自动化测试脚本

1. 在 `$TRT_SOURCE/samples/opensource/LossTest/` （即与 `losstest.cpp` 相同目录下）创建 Python 脚本 `buildcpp.py` 自动生成 `losstest.cpp` 文件：

   ```bash
   python buildcpp.py -i h -o f -x kEXP
   ```

2. 在 `$TRT_SOURCE/build/` 下使用 `check.sh` 执行 `make` 和 `out/loss_test` ，成功的话会输出结果并创建日志。

   ```bash
   sh check.sh
   ```

3. 测试完一组 `OP-INPUT` 之后去 `$TRT_SOURCE/build/out/logs/` 下计算精度误差：

   ```bash
   python calc_loss.py -i h -o f -x kEXP
   ```

## 加强版自动化测试脚本

1. 将一个 `Unary::Operation` 的 `buildcpp` 和 `check.sh` 步骤聚合，由于不同输入精度需要不同输入数据，需要分开三个聚合脚本：

   - `runtest.float.sh`
   - `runtest.int.sh`
   - `runtest.bool.sh`

   此外还需要传入 `Unary::Operation` 参数，如 `kEXP` `kLOG` 。

2. 脚本类似：

   ```bash
   # runtest.float.sh
   # 参数 $1 为 Unary::Operation 算子名
   # 开头都要重新算标准 kFLOAT - kFLOAT 精度
   python buildcpp.py -x $1 -d f -i f -o f && sh $TRT_SOURCE/build/check.sh
   
   # 测试 kFLOAT 输入
   python buildcpp.py -x $1 -d f -i f -o f && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i f -o h && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i f -o i8 && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i f -o i32 && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i f -o b && sh $TRT_SOURCE/build/check.sh
   
   # 测试 kHALF 输入
   python buildcpp.py -x $1 -d f -i h -o f && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i h -o h && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i h -o i8 && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i h -o i32 && sh $TRT_SOURCE/build/check.sh
   python buildcpp.py -x $1 -d f -i h -o b && sh $TRT_SOURCE/build/check.sh
   ```

   

## 其他

## Appendix

### 算子列表

- `kEXP`

- `kLOG`

- `kRECIP` (Reciprocal) 取倒数

- `kSQRT`

- `kABS`

- `kNEG` 取相反数

- 三角函数系：

  - `kSIN`

  - `kCOS`

  - `kTAN`

  - `kSINH` 双曲正弦 (hyperbolic sine function) : $\text{sinh}(x)=\dfrac{e^x-e^{-x}}{2}$

  - `kCOSH` 双曲余弦 (hyperbolic cosine function) : $\text{cosh}(x) = \dfrac{e^x+e^{-x}}{2}$

  - `kASIN`

  - `kACOS`

  - `kATAN`

  - `kASINH` 反双曲正弦 (inverse hyperbolic sine function): $\text{asinh}(x)=\text{ln}(x+\sqrt{x^2+1}), (-\infty, +\infty)$

  - `kACOSH` 反双曲余弦 (inverse hyperbolic cosine function): $\text{acosh}(x)=\text{ln}(x+\sqrt{x^2-1}), [1,+\infty)$

  - `kATANH` 反双曲正切 (inverse hyperbolic tangent function): $\text{atanh}(x)=\text{ln}\sqrt{\dfrac{1+x}{1-x}}, (-1,1)$

    

### losstest.cpp

此 `cpp` 用于测试运行，由于需要改变输入输出类型和算子，后期使用的是 `buildcpp.py` 根据命令行参数自动生成对应的 `losstest.cpp` 文件。

```cpp
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
```







