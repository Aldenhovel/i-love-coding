# Construct ABS Network

## sampleMNISTAPI

sampleMNISTAPI 与 sampleMNIST 不同是它采用 C++ 接口搭建 CNN 模型再从 `mnistapi.wts` 文件加载经过 TF 训练过的权值来推理 MNIST 数据集。

>The sampleMNISTAPI example demonstrates how to use the TensorRT C++ API to create a simple convolutional neural network (CNN) for recognizing handwritten digits from the MNIST dataset.
>
>The example code loads a pre-trained TensorFlow model, converts it to a TensorRT network using the Parser API, and then optimizes the network for inference on an NVIDIA GPU using the Builder API. Finally, the example uses the Engine API to run inference on a batch of test images and outputs the predicted class probabilities.

## 修改

### 备份原文件

备份 `$TRT_SOURCE/samples/opensource/sampleMNISTAPI/sampleMNISTAPI.cpp` 

### 修改网络

修改原 `sampleMNISTAPI.cpp` 中 `constructNetWork` 部分：

```cpp
bool SampleMNISTAPI::constructNetwork(SampleUniquePtr<nvinfer1::IBuilder>& builder,
    SampleUniquePtr<nvinfer1::INetworkDefinition>& network, SampleUniquePtr<nvinfer1::IBuilderConfig>& config)
{
    ITensor* data = network->addInput(
        mParams.inputTensorNames[0].c_str(), DataType::kFLOAT, Dims3{1, mParams.inputH, mParams.inputW});
    assert(data);
	
    // add a unary later for abs operation, connect data -> abslayer
    IUnaryLayer* absLayer = network->addUnary(*data, UnaryOperation::kABS);
    assert(absLayer);
	
    // mark abslayer's output is the network's output
    absLayer->getOutput(0)->setName(mParams.outputTensorNames[0].c_str());
    network->markOutput(*absLayer->getOutput(0));

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
```

>**TensorTR API 中新建层的操作**
>
>1. **在网络中添加输入（层）**
>
>   ```cpp
>     ITensor* data = network->addInput(
>     	mParams.inputTensorNames[0].c_str(), // 设置输入张量名
>         DataType::kFLOAT, // float 类型
>         Dims3{1, mParams.inputH, mParams.inputW}); // 形状为 [1, 28, 28] 这里不考虑 batch 维度
>     assert(data);
>   ```
>
>2. **在网络中添加卷积层**
>
>   ```cpp
>     IConvolutionLayer* conv1 = network->addConvolutionNd(
>         *scale_1->getOutput(0), // 输入取上一层的输出
>         20, // 卷积输出通道数，这里表示有 20 个卷积核
>         Dims{2, {5, 5}, {}}, // 卷积核大小，这里是 2d 卷积核， 5 X 5 大小， 没有 batch 维度
>         mWeightMap["conv1filter"], // 卷积核 weight , 这是一个 Map 所以以键值对方式存储参数，这些参数在 loadWeights() 中已经加载好
>         mWeightMap["conv1bias"] // 卷积核 bias
>     );
>     assert(conv1); // 检查层构建是否有效
>     conv1->setStride(DimsHW{1, 1}); // 设置 stride = (1, 1)
>   ```
>
>   `network->addConvolutionNd()` 中参数 `mWeightMap` `mWeightMap` 好像是必须提供的，没有不提供此参数的重载。
>
>3. **在网络中添加池化层**
>
>   ```cpp
>     IPoolingLayer* pool1 = network->addPoolingNd(*conv1->getOutput(0), PoolingType::kMAX, Dims{2, {2, 2}, {}});
>     assert(pool1);
>     pool1->setStride(DimsHW{2, 2});
>   ```
>
>    这段代码将 `conv1` 层的输出作为输入，设置池化类型为 `PoolingType::kMAX` ，指定 2d 卷积核 大小为 2 X 2，batch 维度置空。
>
>4. **在网络中添加全连接层**
>
>   ```cpp
>     IFullyConnectedLayer* ip1 = network->addFullyConnected(
>     	*pool2->getOutput(0), // 以 pool2 层输出作为输入 
>         500, // 输出的神经元个数
>         mWeightMap["ip1filter"], // 权重参数 
>         mWeightMap["ip1bias"]
>     );
>     assert(ip1);
>   ```
>
>5. **在网络中添加 SoftMax 层**
>
>   ```cpp
>     ISoftMaxLayer* prob = network->addSoftMax(*ip2->getOutput(0));
>     assert(prob);
>   ```
>
>     在TensorRT中，`ISoftMaxLayer`层默认对最后一个维度进行 softmax 操作。
>
>6. **添加元操作**
>
>   ```cpp
>   IUnaryLayer* absLayer = network->addUnary(*data, UnaryOperation::kABS);
>   assert(absLayer);
>   ```
>
>7. **标记输出结果**
>
>   ```cpp
>     prob->getOutput(0)->setName(mParams.outputTensorNames[0].c_str()); // 设置 prob 输出的名
>     network->markOutput(*prob->getOutput(0)); // 将 prob 标记为 network 输出
>   ```

### 修改输入数据

原程序在 `processInput()` 中设置 `std::vector<uint8_t>` 来记录由 `readPGMFile()` 读取的数据：

```cpp
// Read a random digit file
srand(unsigned(time(nullptr)));
std::vector<uint8_t> fileData(mParams.inputH * mParams.inputW);
mNumber = rand() % mParams.outputSize;
readPGMFile(locateFile(std::to_string(mNumber) + ".pgm", mParams.dataDirs), fileData.data(), mParams.inputH, mParams.inputW);
```

经过输出检视后再进行初步预处理：转化为 `float` 变量并减去均值作归一化：


```cpp
// Subtract mean from image
float* hostDataBuffer = static_cast<float*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
{
	hostDataBuffer[i] = float(fileData[i]) - meanData[i];
}
```

现在我们需要构造一个存在正负的张量代替原来传入文件：

```cpp
srand(unsigned(time(nullptr)));
int positivePixels = rand() % mParams.inputH * mParams.inputW; // 正的部分长度不超过 H * W
std::vector<float> fileDataPositive(positivePixels, 1.0f); // 生成正的部分，是一个 vector<float>
std::vector<float> fileDataNegative(mParams.inputH * mParams.inputW - positivePixels, -1.0f); // 同理负的部分
std::vector<float> fileData; // 后面构造一个 fileData 来拼接这两个 vector 代替原程序中的读取文件
fileData.insert(fileData.end(), fileDataPositive.begin(), fileDataPositive.end());
fileData.insert(fileData.end(), fileDataNegative.begin(), fileDataNegative.end());
```

原本预处理的步骤现在也不需要了，不然会影响结果：

```cpp
// Subtract mean from image
float* hostDataBuffer = static_cast<float*>(buffers.getHostBuffer(mParams.inputTensorNames[0]));
for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
{
	hostDataBuffer[i] = float(fileData[i]);//; - meanData[i];
}
```

### 修改输入预览

源程序输入为 `uint8_t` 并使用字符预览图象：

```cpp
// Print ASCII representation of digit image
std::cout << "\nInput:\n" << std::endl;
for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
{
	std::cout << (" .:-=+*#%@"[fileData[i] / 26]) << (((i + 1) % mParams.inputW) ? "" : "\n");
}
```

现在因为输入是有符号数，而且需要以正负值区别，因此需要修改此预览代码：

```cpp
std::cout << "\nInput:\n" << std::endl;
for (int i = 0; i < mParams.inputH * mParams.inputW; i++) std::cout << fileData[i] << std::endl; //输出数值
for (int i = 0; i < mParams.inputH * mParams.inputW; i++) // 以 + - 输出正负图像
{
	std::cout << ("-+"[fileData[i] >= 0? 1: 0]) << (((i + 1) % mParams.inputW) ? "" : "\n");
}
```

### 修改输出预览

原程序中得到一个 `size=10` 的 `float*` 作为输出，在控制台按照格式打印出来：

```cpp
bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
{
    float* prob = static_cast<float*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
    std::cout << "\nOutput:\n" << std::endl;
    float maxVal{0.0f};
    int idx{0};
    for (int i = 0; i < mParams.outputSize; i++)
    {
        if (maxVal < prob[i])
        {
            maxVal = prob[i];
            idx = i;
        }
        std::cout << i << ": " << std::string(int(std::floor(prob[i] * 10 + 0.5f)), '*') << std::endl;
    }
    std::cout << std::endl;
    return idx == mNumber && maxVal > 0.9f;
}
```

现在我们输出的图像数据应该也是 `H * W` 与输入一致，因此可以参考预览输入时的语句将这个输出也打印出来：

```cpp
bool SampleMNISTAPI::verifyOutput(const samplesCommon::BufferManager& buffers)
{
    float* prob = static_cast<float*>(buffers.getHostBuffer(mParams.outputTensorNames[0]));
    std::cout << "\nOutput:\n" << std::endl;

    for (int i = 0; i < mParams.inputH * mParams.inputW; i++) std::cout << prob[i] << std::endl;
    for (int i = 0; i < mParams.inputH * mParams.inputW; i++)
    {
        std::cout << ("-+"[prob[i] >= 0? 1: 0]) << (((i + 1) % mParams.inputW) ? "" : "\n");
    }
	return true
}
```

### 上传并编译

修改代码后上传到 `$TRT_SOURCE/samples/opensource/sampleMNISTAPI/` 下替换同名文件 `sampleMNISTAPI.cpp` ，然后返回 `$TRT_SOURCE/build/` 下执行 `make` ，应该会通过重新编译。

```bash
(base) xavier@xavier:~/trainee/TensorRT/build/samples/opensource/sampleMNISTAPI$ make
[  5%] Built target third_party.protobuf
[  8%] Built target gen_onnx_proto
[ 14%] Built target third_party.protobuf_aarch64
[ 20%] Built target onnx_proto
[ 25%] Built target nvonnxparser
[ 77%] Built target nvinfer_plugin
[ 77%] Built target caffe_proto
[100%] Built target nvcaffeparser
[100%] Building CXX object samples/opensource/sampleMNISTAPI/CMakeFiles/sample_mnist_api.dir/sampleMNISTAPI.cpp.o
[100%] Linking CXX executable ../../../out/sample_mnist_api
[100%] Built target sample_mnist_api
```

### 运行

返回 `$TRT_SOURCE/build/out/` 执行 `./sample_mnist_api` 检查输出：

```
Input:

1
1
1
-1
-1
-1
-1
-1
-1
+++
---
---

Output:

1
1
1
1
1
1
1
1
1
+++
+++
+++
&&&& PASSED TensorRT.sample_mnist_api # ./sample_mnist_api
```

所有值都已经成功执行 `abs` 操作。

## 分析

1. 程序 C++ `main` 函数流程：

   ```
   int main():
   	prase Args
   	define Logs
   	create SampleMNISTAPI sample
   	
   	sample.build()
   	sample.infer()
   	sample.teardown()
   ```

   需要在 `SampleMNISTAPI` 中修改网络结构，然后在 `infer()` 中修改推理的输入输出形式。

2. 搭建模型 `sample.build()` 流程：

   ```
   bool build():
   	builder = nvinfer::createInferBuilder()
   	network = builder->creatNetwork()
   	config = builder->createBuilderConfig()
   	
   	constructNetwork(builder, network, config)
   ```

    在 `constructNetworfk()` 函数中真正开始搭建模型：

   ```
   bool constructNetwork():
   	build Layers
   	......
   	
   	build Engine
   	......
   ```

3. 使用 `sample.infer()` 推理流程：

   ```
   bool infer():
   	create BufferManager buffers
   	create IExcutionContext context
   	
   	processInput()
   	buffers.copyInputToDevice()
   	context->excute()
   	buffers.copyOutputToHost()
   	verify()
   ```

4. 使用 `sample.teardown()` 清理占用内存，释放指针。









