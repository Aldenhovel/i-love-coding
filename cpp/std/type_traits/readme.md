# type_traits 类型检查

## 简介

因为 C++ 不能像 Java 或 C# 一样所有类型继承自 Object 因此在判断类型方面比较麻烦，而 C++11 提供了判断变量类型的模板函数，用于判断两个类型是否一致。

## std::is_same::value

用于严格检查两个类型是否相等。

```cpp
#include <type_traits>

std::cout << std::is_same<int, float>:: value << std::endl;
```

判断非常严格：

```cpp
std::is_same<int, int32_t>::value;			// true
std::is_same<int, int64_t>::value;			// false
std::is_same<float, int32_t>::value;		// false
std::is_same<int, int>::value;				// true
std::is_same<int, unsigned int>::value;		// false
std::is_same<int, signed int>::value;		// true, int == signed int
std::is_same<char, char>::value;			// true, char != signed/unsigned char
std::is_same<char, unsigned char>::value;	// false
std::is_same<char, signed char>::value;		// false

// char 与 unsigned char / signed char 表达范围是否一样取决于编译器，一般等同于 signed char ，但是类型就是不一样
```



## std::decay

`std::decay` 用于类型退化，实际上就是把各种修饰去除。包括：

- 数值和函数转化为指针和函数指针。
- 去除 `const` `volatile` 修饰。
- 引用转换为值类型。

```cpp
// 这里设置了一个 decay_equiv 结果继承 is_same<T, U> 运算后的类 ::type ，这个类的 ::value 属性可以直接输出
template <typename T, typename U>
struct decay_equiv: std::is_same<typename std::decay<T>::type, U>::type {};

//main 以下结果全为 true
decay_equiv<int, int>::value;
decay_equiv<int, int&>::value;
decay_equiv<int, int&&>::value;
decay_equiv<int, const int&>::value;
decay_equiv<int*, int[2]>::value;
decay_equiv<int(int), int(*)(int)>::value; // int(int) 指输出返回都是 int 的函数， int(*)(int) 是函数指针写法
```



## 总结

- 在模板里可以通过 `std::is_same` 判断模板的类型，从而实现对不同类型的区别对待。
- 在堆类型要求不是非常严格的情况下，可以使用 `std::decay` 把类型退化为基本形态，结合 `std::is_same` 用，可以判断出更多的情况。