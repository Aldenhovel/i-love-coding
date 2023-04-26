# TestElementWiseLoss

## 目标

1. 测试 `ElementWiseLayer` 输入输出类型精度变化，重点测试 `float` `half` `int8` `int32` 输入、输出精度。

   | `ElementWiseLayer::` |                                                              |
   | :------------------: | :----------------------------------------------------------: |
   |       `kSUM `        |                 Sum of the **two** elements.                 |
   |       `kPROD `       |               Product of the **two** elements.               |
   |       `kMAX `        |               Maximum of the **two** elements.               |
   |       `kMIN `        |               Minimum of the **two** elements.               |
   |       `kSUB `        |         Substract the second element from the first.         |
   |       `kDIV `        |           Divide the first element by the second.            |
   |       `kPOW `        |    The first element to the power of the second element.     |
   |    `kFLOOR_DIV `     |      Floor division of the first element by the second.      |
   |       `kAND `        |                 Logical AND of two elements.                 |
   |        `kOR `        |                 Logical OR of two elements.                  |
   |       `kXOR `        |                 Logical XOR of two elements.                 |
   |      `kEQUAL `       |               Check if two elements are equal.               |
   |     `kGREATER `      | Check if element in first tensor is greater than corresponding element in second tensor. |
   |       `kLESS `       | Check if element in first tensor is less than corresponding element in second tensor. |

2. 使用 `Iidentity` 层转化精度，设置在 `output` 前，此层支持：

   `(kFLOAT | kHALF | kINT32 | kBOOL)` -> `(kFLOAT | kHALF | kINT32 | kBOOL)`

   ```cpp
   // 这里使用 IIdentityLayer 实现可靠的 float half int8_t int32_t bool 转化
   IIdentityLayer* identityLayer = network->addIdentity(*opLayer->getOutput(0));
   identityLayer->setOutputType(0, mParams.outType);
   identityLayer->getOutput(0)->setType(mParams.outType);
   assert(identityLayer);
   ```


3. 先初始化编译程序

   ```bash
   cd trainee/TensorRT/
   export TRT_SOURCE=`pwd`
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/xavier/trainee/TensorRT/build/out
   ```

   

## 根据 `concatnet` 建立新项目并编译

1. 在 `$TRT_SOURCE/samples/opensource/` 里面创建 `EWLossTest/` , C++ 主文件为 `ewlosstest.cpp` 。

2. 根据 `sampleMNISTAPI` 的模板编写 `CMakeLists.txt` ：

   ```cmake
   SET(SAMPLE_SOURCES
       ewlosstest.cpp
   )
   set(SAMPLE_PARSERS "caffe")
   include(../../CMakeSamplesTemplate.txt)
   ```

3. 将 `concatnet.cpp` 移动到 `EWLossTest/` 改名 `ewlosstest.cpp` 。

4. 返回 `$TRT_SOURCE/build` 目录编译：

   ```bash
   cd $TRT_SOURCE/build
   cmake .. -DTRT_LIB_DIR=$TRT_RELEASE/lib -DTRT_OUT_DIR=`pwd`/out
   make -j$(nproc)
   ```

5. 更新快捷脚本 `check.sh` ：

   ```bash
   cd $TRT_SOURCE/build/samples/opensource/EWLossTest/
   make
   cd $TRT_SOURCE/build/out
   ./ew_loss_test
   ```

   ```bash
   sh check.sh
   ```

   运行成功即可。

## 精简化 `ConcatNet.cpp` 

1. `ElementWiseOperation` 与 `UnaryOperation` 不同需要两个不同元素，因首先精简 `EWLossTest.cpp` 。

## 修改 `EWLossTest.cpp`

### 精度运算的相关设置

1. 使用 `half` 和 `int8_t` `int32_t` 需要引入库：

   ```cpp
   #include <cuda_fp16.h>
   #include <cstdint>
   
   // main
   args.runInFp16 = true;
   args.runInInt8 = true;
   ```

### 修改宏

1. `#define IN_TYPE_A DataType::kFLOAT`
2. `#define IN_TYPE_B DataType::kFLOAT`
3. `#define OUT_TYPE DataType::kFLOAT`
4. `#define IN_VALUE_TYPE_A float`
5. `#define IN_VALUE_TYPE_B float`
6. `#define OUT_VALUE_TYPE float`

### 修改 `mParams` 参数

1. `DataType inTypeA = IN_TYPE_A`
2. `DataType inTypeB = IN_TYPE_B`
3. `DataType outType = OUT_TYPE`

### 修改 `Input` 和加入 `IIdentityLayer` 转化层

1. 两个 `ITensor` 需要分别接受 `IN_TYPE_A` `IN_TYPE_B` 输入类型：

   ```cpp
   ITensor* tensor1 = network->addInput(
       mParams.inputTensorNames[0].c_str(), mParams.inTypeA, Dims3{1, mParams.input1_H, mParams.input1_W});
   assert(tensor1);
   
   ITensor* tensor2 = network->addInput(
       mParams.inputTensorNames[1].c_str(), mParams.inTypeB, Dims3{1, mParams.input2_H, mParams.input2_W});
   assert(tensor2);
   ```

2. `ElementWiseLayer` / `IconcatenationLayer` 设置：

   ```cpp
   // IConcatenationLayer
   ITensor* tensors[] = {tensor1, tensor2};
   IConcatenationLayer* concatLayer = network->addConcatenation(tensors, 2);
   assert(concatLayer);
   concatLayer->setAxis(mParams.concatDim);
   
   // IElementWiseLayer & kSUM
   IElementWiseLayer* opLayer = network->addElementWise(*tensor1, *tensor2, ElementWiseOperation::kSUM);
   assert(opLayer);
   ```
   
3. `IIdentityLayer` 需要接在 `ElementWiseLayer` / `IConcatenationLayer` 的后面，例如：

   ```cpp
   IIdentityLayer* identityLayer = network->addIdentity(*concatLayer->getOutput(0));
   identityLayer->setOutputType(0, mParams.outType);
   identityLayer->getOutput(0)->setType(mParams.outType);
   assert(identityLayer);
   
   identityLayer->getOutput(0)->setName(mParams.outputTensorNames[0].c_str());
   network->markOutput(*identityLayer->getOutput(0));
   ```

   

### 修改 `processInput`

1. `concat`

   >在 `concatenation` 操作中两个高位张量分别输出（假设是 2-D 张量）。
   >
   >```cpp
   >bool SampleMNISTAPI::processInput(const samplesCommon::BufferManager& buffers)
   >{
   >        std::vector<IN_VALUE_TYPE_A> DataA(mParams.input1_H * mParams.input1_W, 1);
   >        std::vector<IN_VALUE_TYPE_B> DataB(mParams.input2_H * mParams.input2_W, 1);
   >
   >        std::cout << "\nInput A:\n" << std::endl;
   >        for (int i = 0; i < mParams.input1_H * mParams.input1_W; i++) std::cout << static_cast<float>(DataA[i]) << (((i + 1) % mParams.input1_W) ? "" : "\n");
   >
   >        std::cout << "\nInput B:\n" << std::endl;
   >        for (int i = 0; i < mParams.input2_H * mParams.input2_W; i++) std::cout << static_cast<float>(DataB[i]) << (((i + 1) % mParams.input2_W) ? "" : "\n");
   >
   >        IN_VALUE_TYPE_A* hostDataBuffer1 = static_cast<IN_VALUE_TYPE_A*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
   >        IN_VALUE_TYPE_B* hostDataBuffer2 = static_cast<IN_VALUE_TYPE_B*>(buffers.getHostBuffer(mParams.inputTensorNames[1]));
   >        for (int i = 0; i < mParams.input1_H * mParams.input1_W; i++)
   >        {
   >            hostDataBuffer1[i] = IN_VALUE_TYPE_A(DataA[i]);
   >        }
   >        for (int i = 0; i < mParams.input2_H * mParams.input2_W; i++)
   >        {
   >            hostDataBuffer2[i] = IN_VALUE_TYPE_B(DataB[i]);
   >        }
   >        return true;
   >}
   >```

2. `IElementWiseLayer`

   > 主要区别是在输入形状上， `concat` 需要复杂形状而 `IElementWiseOperation` 算子不需要，可以简化为一维序列，其中 `DATA_SIZE = 4` 是全局变量。
   >
   > ```cpp
   > bool SampleMNISTAPI::processInput(const samplesCommon::BufferManager& buffers)
   > {
   >     std::vector<IN_VALUE_TYPE_A> DataA = {0.0f, 0.5f, 1.0f, 1.5f};
   >     std::vector<IN_VALUE_TYPE_B> DataB = {true, false, true, false};
   > 
   >     std::cout << "\nInput A:\n" << std::endl;
   >     for (int i = 0; i < DATA_SIZE; i++) std::cout << static_cast<float>(DataA[i]) << "\n"
   >     std::cout << "\nInput B:\n" << std::endl;
   >     for (int i = 0; i < DATA_SIZE; i++) std::cout << static_cast<float>(DataB[i]) << "\n";
   > 
   >     IN_VALUE_TYPE_A* hostDataBuffer1 = 
   >     	static_cast<IN_VALUE_TYPE_A*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
   >     IN_VALUE_TYPE_B* hostDataBuffer2 = 
   >     	static_cast<IN_VALUE_TYPE_B*>(buffers.getHostBuffer(mParams.inputTensorNames[1]));
   >     
   >     for (int i = 0; i < DATA_SIZE;i++) hostDataBuffer1[i] = IN_VALUE_TYPE_A(DataA[i]);
   >     for (int i = 0; i < DATA_SIZE; i++) hostDataBuffer2[i] = IN_VALUE_TYPE_B(DataB[i]);
   > 
   >     return true;
   > }
   > ```

### 修改 `verifyOutput`

1. `concat`

   >在 `concatenation` 操作中虽然输出是高维张量，但是测量精度形状不重要，直接扁平化输出。
   >
   >```cpp
   >bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
   >{
   >    OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
   >    int dataSize = mParams.input1_H * mParams.input1_W + mParams.input2_H * mParams.input2_W;
   >    std::vector<OUT_VALUE_TYPE> output(prob, prob + dataSize);
   >    std::cout << "\nOutput:\n" << std::endl;
   >    for (int i = 0; i < dataSize; i++) std::cout << static_cast<float>(output[i]) << std::endl;
   >}
   >```
   >
   >此外还需要在 return 前加上写入 log 文件，格式为 `{intypeA}_{intypeB}_{outtype}_{data}_cat.txt`
   >
   >```cpp
   >template<typename T>
   >bool writeVectorToFile(const std::vector<T>& v, const std::string& file_path) {
   >    std:: cout << file_path << std::endl;
   >    std::ofstream out_file(file_path);
   >    if (!out_file.is_open()) {
   >        std::cout << "fail to open log file ." << std::endl;
   >        return false;
   >    }
   >    for (const auto& item : v) {
   >        out_file << item << std::endl;
   >    }
   >    out_file.close();
   >    return true;
   >}
   >
   >// verifyOutput
   >if (!writeVectorToFile(output, log_file_name))
   >{
   >    std::cout << "fail to write log ." << std::endl;
   >    return false;
   >};
   >std::cout << "Done" << std::endl;
   >```
   >

2. `IElementWiseLayer`

   >直接按顺序输出 `DATA_SIZE` 个数据：
   >
   >```cpp
   >bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
   >{
   >    OUT_VALUE_TYPE* prob = static_cast<OUT_VALUE_TYPE*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
   >
   >    std::vector<OUT_VALUE_TYPE> output(prob, prob + DATA_SIZE);
   >    std::cout << "\nOutput:\n" << std::endl;
   >    for (int i = 0; i < DATA_SIZE; i++) std::cout << static_cast<float>(output[i]) << std::endl;
   >
   >    if (!writeVectorToFile(output, log_file_name))
   >    {
   >        std::cout << "fail to write log ." << std::endl;
   >        return false;
   >    };
   >    std::cout << "Done" << std::endl;
   >
   >    return true;
   >}
   >```

### 开始时输出 log 文件名

1. 这一点是为了在后面使用脚本自动测试时，即便遇到错误了也可以看到是哪个文件丢失，在程序入口输出：

   ```cpp
   // main
   std::cout << log_file_name << std::endl;
   ```

   

## 使用 `buildcpp.py` 构建不同精度类型的 `ewlosstest.cpp` 文件

1. 外部参数需要：

   - `-a: intypeA`
   - `-b: intypeB`
   - `-o: outtype` 表示 `IIdentityLayer` 中设置的转换输出类型。
   - `-d: data` 不同的数据初始化方式，两个 `f` `i` `b`  中的字符组成，如 `ff` `bi` 等，表示两个输入数据的类型。
   - ~~`-x: operation` 运算操作，在 `concat` 中不需要，因 `concat` 和 `ElementWiseLayer` 不太一样需要使用指定的层。~~

2. 主要代码：

   ```python
   """
   Example: Concate
   """
   # RAW_CPP_TXT = ...
   
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
   
   code_IN_TYPE_A = typeSet_TRT[typeSet.index(inTypeA)]
   code_IN_VALUE_TYPE_A = typeSet_FN[typeSet.index(inTypeA)]
   
   code_IN_TYPE_B = typeSet_TRT[typeSet.index(inTypeB)]
   code_IN_VALUE_TYPE_B = typeSet_FN[typeSet.index(inTypeB)]
   
   code_OUT_TYPE = typeSet_TRT[typeSet.index(outType)]
   code_OUT_VALUE_TYPE = typeSet_FN[typeSet.index(outType)]
   
   code_LOG_FILENAME = f"./logs/{inTypeA}_{inTypeB}_{outType}_{data}_cat.txt"
   
   code_INIT_INPUT_DATA_A = ""
   if data[0] == "f":
       code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = {0.0f, 0.5f, 1.0f, 1.5f};"
   if data[0] == "i":
       code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = { 1, 2, 3, 4};"
   if data[0] == "b":
       code_INIT_INPUT_DATA_A = "std::vector<IN_VALUE_TYPE_A> DataA = {true, false, true, false};"
   
   code_INIT_INPUT_DATA_B = ""
   if data[0] == "f":
       code_INIT_INPUT_DATA_B = "std::vector<IN_VALUE_TYPE_B> DataB = {0.0f, 0.5f, 1.0f, 1.5f};"
   if data[0] == "i":
       code_INIT_INPUT_DATA_B = "std::vector<IN_VALUE_TYPE_B> DataB = { 1, 2, 3, 4};"
   if data[0] == "b":
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
   ```

## 自动测试脚本 (以 `concat` 为例)

1. 建立 `runtest_cat.sh` 脚本内容应包括：
   - 标准值测试，由于有 `f` `i` `b` 三种数据形式两两组合，共有 $3^2=9$ 种标准值样本。
   - 测试值测试，由于输入数据 `A` `B` 只是随机可以互换，又有 `f` `h` `i8` `i32` `b` 这 $5$ 种数据类型，因此共有 $C(5,2)+5=15$ 种输入，每种输入对应 $5$ 种输出，总共有 $15\times5=75$ 种情况。

2. 全部列出以上情况，并且使用 `2>&1 | tee` 指令保存结果到 `$1.log` 文件方便整理错误，需要加 `-a` 表示追加内容：

   ```bash
   # runtest.sh
   # std values
   python buildcpp.$1.py -a f -b f -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d if && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d bf && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d bi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o f -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   
   # f-f-?
   python buildcpp.$1.py -a f -b f -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b f -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   
   # f-h-?
   python buildcpp.$1.py -a f -b h -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b h -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b h -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b h -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b h -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   
   # f-i8-?
   python buildcpp.$1.py -a f -b i8 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  $1.log
   python buildcpp.$1.py -a f -b i8 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i8 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i8 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i8 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # f-i32-?
   python buildcpp.$1.py -a f -b i32 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i32 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i32 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i32 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b i32 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # f-b-?
   python buildcpp.$1.py -a f -b b -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b b -o h -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b b -o i8 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b b -o i32 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a f -b b -o b -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # h-h-?
   python buildcpp.$1.py -a h -b h -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b h -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b h -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b h -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b h -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # h-i8-?
   python buildcpp.$1.py -a h -b i8 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i8 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i8 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i8 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i8 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # h-i32-?
   python buildcpp.$1.py -a h -b i32 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i32 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i32 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i32 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b i32 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # h-b-?
   python buildcpp.$1.py -a h -b b -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b b -o h -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b b -o i8 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b b -o i32 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a h -b b -o b -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # i8-i8-?
   python buildcpp.$1.py -a i8 -b i8 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i8 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i8 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i8 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i8 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # i8-i32-?
   python buildcpp.$1.py -a i8 -b i32 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i32 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i32 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i32 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b i32 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # i8-b-?
   python buildcpp.$1.py -a i8 -b b -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b b -o h -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b b -o i8 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b b -o i32 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i8 -b b -o b -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # i32-i32-?
   python buildcpp.$1.py -a i32 -b i32 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b i32 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b i32 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b i32 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b i32 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # i32-b-?
   python buildcpp.$1.py -a i32 -b b -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b b -o h -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b b -o i8 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b b -o i32 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a i32 -b b -o b -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   # b-b-?
   python buildcpp.$1.py -a b -b b -o f -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a b -b b -o h -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a b -b b -o i8 -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a b -b b -o i32 -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   python buildcpp.$1.py -a b -b b -o b -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a $1.log
   
   ```


3. `sh` 命令参数与 `buildcpp` 对应，例如测试 `kSUB` :

   ```shell
   sh runtest.sh ksub
   ```
   
   脚本会自动寻找 `buildcpp.ksub.py` 并将 log 输出到 `ksub.log` 中。
   
4. 完成后在对应的 log 文件中使用 `ctrl+f` 查找错误。

## 快速定位错误

1. 这里使用 Python 脚本快速定位错误，在 `cat.log` 或同类日志文件中只需要保留文件名和报错信息，例如：

   ```
   ./logs/b_b_b_bb_ksum.txt
   
   [04/19/2023-16:04:38] [E] [TRT] (Unnamed Layer* 0) [ElementWise]: operation SUM requires inputs with activation or Int32 type.
   ```

2. 使用正则表达式把这两种语句形式过滤出来

   ```python
   # cleanlog.py
   p = re.compile('^\[[0-9]{2}/[0-9]{2}/[0-9]{4}-[0-9]{2}:[0-9]{2}:[0-9]{2}\] \[E\]')
   p2 = re.compile('^\./')
   
   lines = [line for line in lines if (p.match(line) or p2.match(line))]
   print(lines)
   ```

3. 得到的结果使用 `ctrl+f` 查找例如 `/f_f`  `/f_h` `/i8_i32`即可定位到对应两个输入类型，再看看有没有在后面附加报错信息。

