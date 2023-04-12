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

    

  

  



