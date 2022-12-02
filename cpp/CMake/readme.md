# 使用 CMake 生成可执行文件

## 1 CmakeLists.txt

1. **指定 cmake 最小版本**

   ```cmake
   cmake_minimum_required(VERSION 3.4.1)
   ```

   在需要高版本 cmake 时需要加上这句话，提醒用户升级 cmake 再执行后续操作。

2. **项目名称**

   ```cmake
   project(demo)
   ```

   会自动生成 `demo_BINARY_DIR` `demo_SOURCE_DIR` 两个变量。

3. **设置编译类型**

   ```cmake
   add_executable(demo demo.cpp)			# 生成可执行文件
   add_library(common STATIC util.cpp)		# 生成静态库
   add_library(common SHARED util.cpp)		# 生成动态库
   ```

   在 Linux 下生成：

   ```
   demo
   libcommon.a
   libcommon.so
   ```

   在 Windows 下生成：

   ```
   demo.exe
   common.lib
   commob.dll
   ```

4. **设置变量**

   ```cmake
   set(src_list main.cpp)	# 令变量 src_list = main.cpp
   ${src_list}				# 使用变量
   ```

5. **提示信息**

   ```cmake
   message(status "This is SOURCE dir" ${demo_SOURCE_DIR})
   ```

完整示例：

```cmake
# CMakeLists.txt

PROJECT (HELLO)
SET(SRC_LIST main.cpp)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_LIST})	# 将 main.cpp 生成 exe
```

```c++
// main.cpp

#include <iostream>
#include <string>
#include "test.cpp"
int main() {
	sayHello();
	std::cout << "hello world" << std::endl;
	std::string s;
	while (std::getline(std::cin, s) && s.size() > 0){ }
	return 0;
}
```

```c++
// test.cpp

#include <iostream>
void sayHello() {
	std::cout << "hello this is test." << std::endl;
}
```

## 编译

1. 先确保目录下写好 `CMakeLists.txt` 文件。

2. 在 PowerShell 使用命令：

   ```powershell
   cmake .
   ```

   然后会生成一大堆东西，包括一个 VS 项目入口 `.sln` 文件。

3. 在 VS 中打开 `.sln` 文件，右键项目树的 `ALL_BUILD` 选择生成。

4. 生成的 `.exe` 可执行文件在 `\Debug` 目录下，可以双击运行。