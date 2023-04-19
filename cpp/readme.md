# C++

这里存放了一些关于 C++ 的相关程序，有一些是课程实验设计，一些是从 《C++ Primer Plus》 上面摘录下来添加注释的经典案例。这么整理的目的是可以按需查找、快速回顾。

## 指南

|       目录        | 概述                                                         |      from *C++PP*       |
| :---------------: | ------------------------------------------------------------ | :---------------------: |
|      `CMake`      | 简要地介绍了 *CMake* 的使用方法，如何将 C/C++ 源码编译成可执行文件。 |                         |
|   `Exceptions`    | 异常处理、自定义异常的使用方法。                             |                         |
|     `FileIO`      | 用 `fstream` 文件读写，包括 `ifstream` `ofstream` 使用方法和一些实例。 |                         |
|     `FunPtr`      | 函数指针演示。                                               | :ballot_box_with_check: |
| `InitializerList` | C++ `initializer_list` 模板。                                | :ballot_box_with_check: |
|      `Pair`       | 用类模板演示了多个模板参数的情况。                           | :ballot_box_with_check: |
|      `Point`      | 展示了关键字 `explicit` 的使用场景，即限制隐式类型转化。     |                         |
|     `QueueTP`     | 使用类模板的队列，包含了 `QueueTP->Node->Item` 的嵌套类。    | :ballot_box_with_check: |
|      `RTTI`       | *Runtime Type Identification* ，包括 `dynamic_cast` `const_cast` `static_cast` `typeid` 的使用场景。 | :ballot_box_with_check: |
|    `SmartPtr`     | 智能指针简介，包含 `auto_ptr` `shared_ptr` `unique_ptr` 。   | :ballot_box_with_check: |
|      `Sort`       | 收集了常见的一些排序算法。                                   |                         |
|      `Stack`      | 展示了类模板的构造方法。                                     | :ballot_box_with_check: |
|     `String`      | 收集了 `string` 模板的常用方法，例如字符串拼接、查找、替换子串等。 |                         |
|      `Time`       | 示范了类的基础使用方法。                                     | :ballot_box_with_check: |
|    `Tempmemb`     | 演示了成员模板（变量和函数使用模板）的使用方法。             | :ballot_box_with_check: |
|   `TempNFriend`   | 演示了类模板与友元、静态成员的特性。                         | :ballot_box_with_check: |
|  `TennisPlayer`   | 示范了基础的继承、虚函数的使用方法。                         | :ballot_box_with_check: |
|    `ValArray`     | 用于数值计算的 `valarray` 和 `slice` ，以及与 `vector` 的一些比较。 | :ballot_box_with_check: |
|    `Volatile`     | 关键字 `volatile` 的特性：易变、原子性、不可优化。           |                         |
|     `Worker`      | 通过 `Worker-->virtual Singer` , `Worker-->virtual Waiter` , `Singer, Waiter-->SingingWaiter` 来展示虚基类和多重继承的语法、以及需要注意的事项。 | :ballot_box_with_check: |


## std

与 `STL` 和 `std::` 下有关的零碎部分，在目录 `std/` 下。

| 目录 `std/...` |                 概述                  |      |
| :------------: | :-----------------------------------: | ---- |
|    `chrono`    |        C++ 高精度时间相关的库         |      |
| `type_traits`  | C++11 类型判断 `is_same` `decay` 使用 |      |

## TensorRT C++

使用 C/C++ API 开发与部署 Nvidia TensorRT 神经网络模型，在目录 `TensorRT/` 下 。

| 目录 `TensorRT/...` |                             概述                             |      |
| :-----------------: | :----------------------------------------------------------: | ---- |
| `00-sampleMNISTAPI` | 简单地介绍了使用 TensorRT API 搭建网络的方法，和加载 Caffe 模型的方法并对 MNIST 图像推理。 |      |
|     `01-ABSNet`     |     仿照 `sampleMNISTAPI.cpp` 将搭建一个 ABS 算子网络。      |      |
|   `02-ConcatNet`    | 仿照 `sampleMNISTAPI.cpp` 将搭建一个 Concatenation 算子网络。 |      |
|  `03-UnaryLossTest` | 修改 `sampleMNISTAPI.cpp` 为 `losstest.cpp` 可以测试不同 `UnaryOperation` 算子在转换精度后的损失。 |     |
| `04-ElementWiseLossTest` | 在 `03` 的基础上测试更多算子，例如 `sum` `matmul` `concat` 等转换精度后的损失。（待完成） | |

## Q&A

收集关于面经和相关问题。

[quations click me](https://github.com/Aldenhovel/i-love-coding/blob/main/cpp/quations.md)

