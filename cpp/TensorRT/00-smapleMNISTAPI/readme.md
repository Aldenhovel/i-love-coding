# sampleMNIST(API)

这是 NVIDIA TensorRT 使用 C++ API 搭建 CNN 网络推理 MNIST 图像的示例，学习  TensorRT 的起步第一个例子吧。

**这里只是存放这个 sampleMNISTAPI 的代码，要 git 仓库下来编译才能运行**

## 编译仓库

1. `git clone` 仓库到本地。

2. `cd TensorRT && git checkout 7.1.3` 切换分支。

3. `git submodule update --init --recursive` 下载相关子模块。

4. 设置环境变量，编译仓库：

   ```bash
   # now in path/to/TensorRT
   export TRT_SOURCE=`pwd`
   cd $TRT_SOURCE
   mkdir -p build && cd build
   cmake .. -DTRT_LIB_DIR=$TRT_SOURCE/lib -DTRT_OUT_DIR=`pwd`/out
   make -j$(nproc)
   ```

   

5. 为了省事这里先测试下 `sampleMNIST` 能不能跑：

   ```bash
   cd build/sample/opensource/sampleMNIST
   make
   ```

   编译完可能会出现 `libnvcaffeparser.so.7` 没有写进系统环境的情况，手动添加一下即可：

   ```bash
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TRT_SOURCE/build/out
   ```

6. 去 `build/out` 下运行一下：

   ```bash
   cd $TRT_SOURCE/build/out
   ./sample_mnist
   ```

   出现图像和运算结果即可：

   ```
   &&&& RUNNING TensorRT.sample_mnist_api # ./sample_mnist_api
   [03/27/2023-17:16:03] [I] Building and running a GPU inference engine for MNIST API
   [03/27/2023-17:16:03] [I] Loading weights: data/mnist/mnistapi.wts
   [03/27/2023-17:16:09] [I] [TRT] Detected 1 inputs and 1 output network tensors.
   
   Input:
   
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@.*@@@@@@@@@@
   @@@@@@@@@@@@@@@@.=@@@@@@@@@@
   @@@@@@@@@@@@+@@@.=@@@@@@@@@@
   @@@@@@@@@@@% #@@.=@@@@@@@@@@
   @@@@@@@@@@@% #@@.=@@@@@@@@@@
   @@@@@@@@@@@+ *@@:-@@@@@@@@@@
   @@@@@@@@@@@= *@@= @@@@@@@@@@
   @@@@@@@@@@@. #@@= @@@@@@@@@@
   @@@@@@@@@@=  =++.-@@@@@@@@@@
   @@@@@@@@@@       =@@@@@@@@@@
   @@@@@@@@@@  :*## =@@@@@@@@@@
   @@@@@@@@@@:*@@@% =@@@@@@@@@@
   @@@@@@@@@@@@@@@% =@@@@@@@@@@
   @@@@@@@@@@@@@@@# =@@@@@@@@@@
   @@@@@@@@@@@@@@@# =@@@@@@@@@@
   @@@@@@@@@@@@@@@* *@@@@@@@@@@
   @@@@@@@@@@@@@@@= #@@@@@@@@@@
   @@@@@@@@@@@@@@@= #@@@@@@@@@@
   @@@@@@@@@@@@@@@=.@@@@@@@@@@@
   @@@@@@@@@@@@@@@++@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
   Output:
   
   0:
   1:
   2:
   3:
   4: **********
   5:
   6:
   7:
   8:
   9:
   
   &&&& PASSED TensorRT.sample_mnist_api # ./sample_mnist_api
   ```

7. 同理使用 `./sample_mnist_api` 即可运行 sampleMNISTAPI。







