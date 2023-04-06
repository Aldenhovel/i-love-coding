# C++

[TOC]



## basic

### 1 `struct` 和 `class` 关键字的区别？

1.  `class` 支持继承和多态， `struct` 不支持。

2.  `class ` 默认成员 `private` ， `struct`  默认为 `public` (但是也是可以设置为 `private` 的)：

   ```cpp
   struct Person {
   private:
       std::string name;
       int age;
   public:
       void SetName(std::string name) {
           this->name = name;
       }
       
       void SetAge(int age) {
           this->age = age;
       }
   };
   ```

### 2 `extern "C"` 是什么？

1. 在使用 C++ 与 C 代码交互时，需要使用 `extern "C"` 来告诉编译器使用 C 语言的命名和调用约定，以便正确链接和调用 C 代码中的函数。

2. C++ 与 C 语言的命名和调用约定是不同的，这主要是因为 C++ 支持函数重载和类成员函数等特性。在 C++ 中，编译器会根据函数的参数列表和返回值类型来生成不同的函数名称，以便实现函数重载。而在 C 语言中，函数名是唯一的标识符，不支持函数重载。

   因此，在使用 C++ 编写与 C 代码交互的程序时，需要使用 `extern "C"` 来告诉编译器使用 C 语言的命名和调用约定，以便正确链接和调用 C 语言的函数。

3. 例如，下面的示例演示了如何在 C++ 中使用 `extern "C"` 声明一个 C 函数：

   ```cpp
   #ifdef __cplusplus
   extern "C" {
   #endif
   
   void my_c_function();
   
   #ifdef __cplusplus
   }
   #endif
   
   ```

### 3 函数重载和覆盖的区别？

1. **函数重载（Function Overloading）**

   是指在同一个作用域中定义多个函数，它们具有相同的函数名，但是参数列表不同或者参数类型不同，或者参数顺序不同，或者返回类型不同。编译器会根据函数名、参数列表和返回类型等信息来决定使用哪个函数。函数重载可以提高代码的可读性和可维护性，使程序更加灵活。

2. **函数覆盖（Function Overriding）**

   是指派生类中的函数覆盖基类中的虚函数。在基类中，虚函数是用 virtual 关键字声明的成员函数，它允许派生类重写它的实现。在派生类中，如果函数的名称、参数列表和返回类型与基类中的虚函数相同，那么它就覆盖了基类中的虚函数。当通过基类指针或引用调用虚函数时，实际调用的是派生类中覆盖的函数。

3. 总的来说，函数重载是指在同一作用域中定义多个名称相同但参数列表不同的函数，可以用于增加代码的灵活性和可读性；函数覆盖是指在派生类中覆盖基类中的虚函数，用于实现多态性和继承。

### 4 多态是什么，运行时的实现原理是什么？

1. 多态允许同一种操作在不同的对象上有不同的行为。在 C++ 中，多态性通过虚函数来实现，称为虚函数多态性。

2. 在 C++ 中，虚函数的实现原理涉及到虚函数表和虚函数指针。每个对象的内存中会有一个指向虚函数表的指针，虚函数表是一个数组，其中存储了该类及其父类中所有的虚函数地址。当派生类中覆盖基类中的虚函数时，编译器会在派生类的虚函数表中修改对应函数的地址，使其指向派生类的函数实现。这样，在调用虚函数时，会根据对象的实际类型找到该类型对应的虚函数表，并调用其中的函数。

   虚函数的实现原理实现了动态绑定，使得程序在运行时可以根据实际对象的类型来确定调用的函数，从而实现了多态性。

### 5 单继承、多继承、虚继承是什么？

1. **单继承：**

   指派生类只从一个基类继承。单继承的继承方式是最常见的继承方式，它使得代码的组织更加清晰，易于维护和扩展。

2. **多继承：**

   指派生类从多个基类继承。多继承的优点是可以让一个类拥有多个基类的特性，从而实现更加灵活和高效的代码复用，但是也容易引起继承层次复杂和二义性的问题。

3. **虚继承：**

   虚继承是为了解决多继承带来的二义性问题而引入的，它将多个基类继承方式改为虚继承，使得派生类中只包含一个基类子对象。虚继承将多个基类的共同基类放到最顶层，避免了多个基类中拥有相同基类的情况，从而解决了二义性问题。

4. 虚继承的实现原理是在派生类的内存布局中添加一个虚基类指针，该指针指向共同基类的子对象。虚继承也会引入一些性能开销和复杂性，因此应该尽量避免过度使用。

   总之，单继承是最简单、最常用的继承方式，多继承可以实现更加灵活和高效的代码复用，但需要避免二义性问题，而虚继承则是为了解决多继承的二义性问题而引入的。

### 6 为什么不把所有函数都弄成虚函数

1. 虚函数虽然可以实现多态性，但是也会引入一些性能开销和复杂性。每个对象都需要保存一个指向虚函数表的指针，虚函数表本身也需要占用一定的**内存空间**。在多继承和虚继承的情况下，由于可能存在多个虚函数表，这些开销和复杂性还会进一步增加。
2. 此外，不是所有的函数都需要成为虚函数。只有在需要使用多态性的情况下，才需要将函数定义为虚函数。在其他情况下，非虚函数的**调用效率**要高于虚函数，因为非虚函数的调用是静态绑定的，可以在编译期确定调用的函数。

### 7 构造函数、析构函数可以是虚函数吗？

1. **构造函数不能是虚函数**

   因为虚函数是在对象被创建后才能使用的，而构造函数则是用来创建对象的，它们是互相矛盾的。

2. **析构函数可以是虚函数**

   通常当我们使用多态性的时候，需要将基类的析构函数定义为虚函数，这样在删除派生类对象时，会调用正确的析构函数，以避免内存泄漏等问题。

   ```cpp
   class Base {
   public:
       virtual ~Base() {}
   };
   
   class Derived : public Base {
   public:
       ~Derived() {}
   };
   
   int main() {
       Base* ptr = new Derived;
       delete ptr; // 调用正确的析构函数，避免内存泄漏
       return 0;
   }
   
   ```

   在这个例子中 `Base` 的析构函数为虚函数，派生类 `Derived` 的析构函数不需要定义为虚函数，因为它会自动继承基类的虚函数特性。我们通过基类指针 `ptr` 删除派生类对象，由于基类的析构函数是虚函数，所以会调用正确的析构函数，避免了内存泄漏等问题。

### 8 什么是纯虚函数，有什么用？

1. 纯虚函数是在基类中声明但没有定义实现的虚函数。它的语法形式为在函数声明的末尾加上 "= 0"，例如：

   ```cpp
   class Shape {
   public:
       virtual double getArea() const = 0;
   };
   
   ```

   在这个例子中，`getArea()` 函数被声明为纯虚函数，因为在基类中无法给出一个通用的实现，而只能由派生类来实现。一个类如果包含了一个或多个纯虚函数，就被称为**抽象类**。

2. 纯虚函数的作用在于，通过基类中的虚函数接口，**强制要求派生类来实现这些函数**。这种设计思想称为接口隔离原则，它可以确保派生类实现了基类中所定义的接口，从而保证了程序的正确性和可维护性。同时，纯虚函数还可以作为占位符使用，以便在派生类中给出一个具体的实现。

   需要注意的是，**包含纯虚函数的类不能被实例化**，而只能被作为基类来使用。如果派生类没有给出纯虚函数的具体实现，那么它也将成为一个抽象类，无法被实例化。

3. **使用场景**

   - 基类定义了一些函数接口，但是这些函数的具体实现方式取决于派生类，基类不能提供通用的实现方式。

   - 基类是一个抽象概念，不能直接被实例化，只能被用作派生类的基类。

   - 基类希望强制要求派生类必须实现某些函数。

### 9 什么是 RAII？

1. RAII是一种编程技术，全称为“资源获取即初始化”（Resource Acquisition Is Initialization）。它的核心思想是，资源的申请和释放应该在对象的构造和析构过程中自动完成，而不是依赖于程序员手动管理。RAII 通常用于管理资源的类，如文件句柄、内存、互斥锁等，可以保证这些资源在使用完毕后能够正确地被释放，从而避免资源泄露和内存泄露等问题。
2. 在 RAII 中，资源的申请通常在对象的**构造函数**中进行，而资源的释放则在对象的**析构函数**中完成。这样，在对象生命周期结束时，资源就会被自动释放。

### 10 类的大小如何计算

1. 类的大小由类的成员变量和成员函数共同决定。

2. **类成员大小**

   类的成员变量的大小是各个成员变量大小之和，其中需要考虑成员变量的对齐规则。在一些系统中，由于硬件原因，访问未对齐的数据会导致性能下降或者系统崩溃等问题，因此编译器会对成员变量进行对齐操作。对齐规则会根据编译器和平台的不同而有所区别，通常是按照成员变量的类型和当前编译环境的字节对齐要求来确定的。

3. **类函数大小**

   类的成员函数不占用类对象的空间，因为它们是代码段的一部分，每个对象共享同一个函数实现。但是，如果类的成员函数是虚函数，那么会为每个对象增加一个指向虚函数表的指针，这个指针的大小和指针的字节长度有关，通常为 4 或 8 字节。

4. 除了成员变量和成员函数外，类的大小还可能受到编译器和平台的其他限制，如内存对齐、编译器的优化策略等因素的影响。因此，在不同的编译器和平台上，同一个类的大小可能会不同。

5. 使用 C++ 中的 `sizeof` 运算符来计算类的大小。

### 11 `volatile` 关键字有什么用？

1. 用来告诉编译器一个变量不应该进行一些优化，以保证程序的正确性。`volatile` 可以修饰变量、指针、成员函数等。

2. **防止编译器优化**

   如果一个变量被标记为 `volatile`，编译器就不会对它进行优化，以避免在程序执行时发生错误。例如，当一个变量被用作信号量，它可能会在中断处理程序中被修改，因此需要标记为 `volatile`。

3. **指示编译器不要缓存该变量的值**

   如果一个变量被标记为 `volatile`，编译器就不会把该变量的值缓存到 CPU 寄存器或者其他优化的位置，而是直接从内存中读取或写入该变量的值。这样可以确保读取到最新的值，避免出现错误。

4. 示例：

   ```cpp
   #include <iostream>
   
   volatile int g_count = 0; // 编译器不会优化 g_count
   
   void increment_count() {
       ++g_count;
   }
   
   int main() {
       for (int i = 0; i < 10; ++i) {
           increment_count();
           std::cout << "g_count = " << g_count << std::endl;
       }
       return 0;
   }
   
   ```

   

### 12 指针和引用的区别

1. **定义和使用方式不同**

   指针使用 `*` 来声明，引用使用 `&` 来声明。使用指针时需要使用 `new` 来分配内存，使用引用时不需要。

2. **空值问题**

   指针可以指向空值（`nullptr`），引用必须始终引用某个对象。

3. **可以改变指向的对象**

   指针可以在运行时更改指向的对象，而引用不能改变引用的对象。

4. **引用是安全的**

   引用不会像指针一样容易出现未初始化的问题，因为引用必须在定义时初始化。

5. 在选择使用指针还是引用时，通常建议优先使用引用，因为引用更安全、更易读，也更符合C++中的设计理念。但是，在一些情况下，使用指针更方便，例如**需要动态分配内存、运行时需要改变所指对象、需要修改函数参数的值和使用 STL 容器存储对象**等场景。

### 13 `new` 和 `malloc` 区别？

1. `new`是C++中的操作符，而`malloc`是C语言中的函数。
2. `new`会调用对象的构造函数，而`malloc`不会。这意味着，如果需要分配对象类型的内存，使用`new`更方便，因为它可以自动调用构造函数，而不需要显式地调用它。
3. `new`返回的是类型指针，而`malloc`返回的是`void*`。这意味着，在使用`malloc`时，需要进行强制类型转换才能正确地使用返回的指针。而使用`new`则不需要进行类型转换。
4. `new`可以处理数组，而`malloc`不能。如果需要动态分配数组，使用`new[]`更方便，因为它可以自动调用数组元素类型的构造函数。
5. `new`抛出异常，而`malloc`返回`NULL`。如果动态分配内存失败，`new`会抛出异常，而`malloc`会返回`NULL`。这意味着，在使用`new`时需要使用异常处理机制来处理分配内存失败的情况，而在使用`malloc`时需要手动检查返回值是否为`NULL`。
6. 总的来说，C++中的`new`更适合分配对象类型的内存，而C语言中的`malloc`更适合分配简单类型（例如`int`、`char`等）的内存。在使用时，应根据具体情况选择适合的方式。

### 14 `new[]` 和 `delete[]` 是否要搭配使用？

1. 使用`new[]`分配数组时，必须使用`delete[]`释放分配的内存，否则可能导致内存泄漏或者其他的问题。与普通的`new`和`delete`操作符不同，`new[]`和`delete[]`操作符的实现需要保证分配和释放的内存区域是连续的。因此，使用`new[]`操作符分配数组时，需要保证使用`delete[]`操作符释放相同大小的内存区域。

2. 示例：

   ```cpp
   int* arr = new int[10]; // 使用new[]操作符分配一个长度为10的int数组
   // 使用数组
   delete[] arr; // 使用delete[]操作符释放分配的内存
   ```

3. 需要注意的是，使用`delete[]`释放数组内存时，不能只释放数组的一部分，否则会导致内存泄漏和其他问题。同时，对已经释放的数组指针进行再次释放也是错误的，会导致程序崩溃等问题。因此，在使用`new[]`和`delete[]`操作符时，需要小心操作，确保正确使用和释放分配的内存。

### 15 `noexcept` 有什么用？

1. 当在函数声明或定义后加上 `noexcept` 关键字时，表示该函数不会抛出任何异常。

   ```cpp
   void foo() noexcept {}
   ```

2. 好处

   - **优化代码**：由于在程序运行时，如果一个函数被声明为 `noexcept`，编译器就会认为该函数不会抛出异常，进而进行一些优化，例如省略异常处理代码，简化程序结构，提高代码执行效率。
   - **提高可靠性**：对于那些对异常处理有严格要求的系统，使用 `noexcept` 关键字可以提高程序的可靠性，因为它保证了程序在该函数中不会发生异常。
   - **让使用者了解函数**：当一个函数被指定为 `noexcept` 时，使用该函数的人会清楚地知道该函数是否会抛出异常，进而更好地编写代码。

3. 需要注意的是，如果一个函数被指定为 `noexcept`，但实际上该函数抛出了异常，程序会调用 `std::terminate()`，从而**导致程序异常终止**。因此，需要确保在使用 `noexcept` 关键字时，函数的实现不会抛出异常。

## C++11

### 1 什么是 `auto` 和 `decltype` ?

1. `auto`关键字可以自动推导变量的类型，可以在声明变量时根据初始化表达式自动推断出变量的类型，从而避免了手动指定变量类型的繁琐过程。例如：

   ```cpp
   auto i = 10; // i被自动推断为int类型
   auto d = 3.14; // d被自动推断为double类型
   auto str = "hello"; // str被自动推断为const char*类型
   ```

2. `decltype`关键字可以获取表达式的类型，可以在编译期间获取表达式的类型，从而可以在类型推导和模板元编程中发挥重要作用。例如：

   ```cpp
   int i = 10;
   decltype(i) j = 20; // j被推断为int类型
   
   const int& foo();
   decltype(foo()) x = 0; // x被推断为const int&类型
   
   ```

### 2 什么是左值(Lvalues)和右值(Rvalues)？

1. 左值指的是表达式所表示的内存位置，通常可以作为赋值语句的左侧操作数，也可以取址、引用和修改。左值可以是变量、数组元素、类成员、返回左值引用类型的函数等。例如：

   ```cpp
   int i = 10; // i是左值
   int arr[5]; // arr是左值
   std::string str = "hello"; // str是左值
   ```

2. 右值指的是表达式所表示的数值或对象，通常不能作为赋值语句的左侧操作数，也不能取址、引用和修改。右值可以是字面量、临时对象、返回右值引用类型的函数等。例如：

   ```cpp
   int a = 10; // 10是右值
   int b = a + 20; // a + 20是右值
   int&& f() { return 42; } // f()返回右值引用类型
   ```

3. C++11引入了右值引用（Rvalue references）的概念，允许程序员直接访问右值，并将其传递到函数中进行移动语义的操作，从而避免不必要的拷贝和分配开销，提高代码的性能和效率。

### 3 什么是左值引用和右值引用？

1. 左值引用是对左值进行引用的一种类型，用于指向已经存在的左值，它通过使用&符号进行声明。例如：

   ```cpp
   int i = 42;
   int& r = i; //r是i的引用，即r和i指向同一个内存地址，它们是等价的。
   ```

2. 右值引用是对右值进行引用的一种类型，用于指向临时对象、将要销毁的对象等右值，它通过使用&&符号进行声明。例如：

   ```cpp
   int&& a = 42;
   int&& b = std::move(a); //使用std::move进行右值引用
   /*
   在上面的例子中，a是右值引用，指向临时对象42，b通过std::move将a的值进行了转移，现在b指向了42，a成为了无效的引用。
   */
   ```

3. 左值引用和右值引用的主要区别在于它们可以绑定的对象的类型。左值引用只能绑定到左值上，而右值引用只能绑定到右值上。此外，右值引用还可以通过std::move等函数将一个左值强制转换为右值引用，从而实现资源的移动语义。

4. 右值引用可以用于移动语义 (Move Semantic) 和完美转发 (Perfect Forwarding) 。

### 4 什么是移动语义？

1. 移动语义（Move Semantics）是C++11引入的一个重要概念，它通过**右值引用**（Rvalue Reference）实现了**对象的高效移动和转移语义，避免了无谓的复制和分配**。
2. 在C++中，对象的拷贝构造函数和赋值运算符（Copy Constructor和Copy Assignment Operator）常常会进行对象的深拷贝（Deep Copy），即将原有的对象内容复制到一个新的内存空间中。这样的操作在对象较大时会带来显著的性能损失，因此需要寻找更高效的实现方式。
3. 移动语义通过定义移动构造函数（Move Constructor）和移动赋值运算符（Move Assignment Operator），将对象的资源所有权从一个对象转移到另一个对象，避免了对象的复制和分配，从而提高了程序的性能和效率。
4. 示例：上面 *3.2* 的例子就是使用了移动语义将 `a` 的资源移动到了 `b` 上面。

### 5 什么是完美转发？

1. 先来看一个不完美转发的例子

   ```cpp
   #include <iostream>
   #include <string>
   
   void print(const std::string& str) {
       std::cout << str << std::endl;
   }
   
   void wrapper(const std::string& str) {
       print(str);
   }
   
   int main() {
       std::string my_string = "Hello World";
       wrapper(my_string);
       return 0;
   }
   ```

   这里通过 `my_string --> wapper() --> print()` 的方式输出了一个字符串，这里是没问题的，但是如果将 `print(const string&)` 定义为 `print(const string)` 这样在对传入的 `const string& my_string` 就会发生强制转换导致 `my_string` 数据类型发生变化，导致丢失信息。

2. 完美转发是指将函数的**参数以原样（包括左值或右值属性）转发到另一个函数中，且不会丢失原参数的信息**。这个特性在C++11中引入，主要通过使用模板来实现。

3. 在函数模板中，完美转发通常通过使用`std::forward`来实现。`std::forward`是一个模板函数，接收一个模板参数和一个参数，并根据参数的左值或右值属性来将参数转发到另一个函数中。当参数是左值时，`std::forward`返回左值引用，当参数是右值时，返回右值引用。

4. 示例：

   ```cpp
   #include <iostream>
   #include <utility>
   
   void foo(int& x)
   {
       std::cout << "foo(int&): " << x << std::endl;
   }
   
   void foo(int&& x)
   {
       std::cout << "foo(int&&): " << x << std::endl;
   }
   
   template<typename T>
   void bar(T&& x)
   {
       foo(std::forward<T>(x));
   }
   
   int main()
   {
       int a = 42;
       bar(a); //调用 foo(int&)
       bar(13); //调用 foo(int&&)
       return 0;
   }
   
   ```

### 6 怎样列表初始化？

1. C++11引入了列表初始化（List Initialization）语法，用于初始化数组、STL容器、类对象等。

2. 示例：

   ```cpp
   int arr[] = {1, 2, 3};
   std::vector<int> vec = {1, 2, 3};
   std::unordered_map<std::string, int> umap = {{"apple", 1}, {"orange", 2}};
   ```

### 7 `std::function` 是什么？

1. `std::function` 是一个通用的函数封装，类似于函数指针，可以用于存储任意可调用对象，如函数、函数指针、成员函数指针、函数对象等。例如：

   ```cpp
   #include <iostream>
   #include <functional>
   
   void foo(int x, int y) {
       std::cout << "x + y = " << x + y << std::endl;
   }
   
   int main() {
       std::function<void(int, int)> f = foo;
       f(1, 2);
       return 0;
   }
   ```

### 8 `std::bind` 是什么？

1. `std::bind` 用于将函数对象和其参数绑定起来，生成一个新的函数对象，也就是一个函数适配器。这个新的函数对象可以方便地在需要的时候调用，不必再重复输入参数。例如：

   ```cpp
   #include <iostream>
   #include <functional>
   
   void foo(int x, int y) {
       std::cout << "x + y = " << x + y << std::endl;
   }
   
   int main() {
       auto f1 = std::bind(foo, 1, 2);
       f1();
       auto f2 = std::bind(foo, std::placeholders::_1, 2);
       f2(1);
       return 0;
   }
   /*
   这里，f1是一个函数对象，等价于调用foo(1, 2)，f2是另一个函数对象，等价于调用foo(1, 2)。
   */
   ```

### 9 C++11 怎么使用 Lambda 表达式？

1. Lambda表达式是C++11新增的一种语法，用于定义匿名函数。它的基本形式如下：

   ```
   [capture list](parameter list) -> return type { function body }
   ```

   `capture list` 用于捕获外部变量，可以为空；`parameter list` 用于定义参数列表，可以为空；`return type` 用于定义返回值类型，可以为空；`function body` 是函数体。

2. 示例：

   ```cpp
   #include <iostream>
   #include <vector>
   #include <algorithm>
   
   int main() {
       std::vector<int> vec = {1, 2, 3, 4, 5};
       int n = 3;
       auto it = std::find_if(vec.begin(), vec.end(), [n](int x) { return x > n; });
       std::cout << *it << std::endl;
       return 0;
   }
   ```



### 10 什么是智能指针 `unique_ptr` ？

1. `unique_ptr` 是一种**独占式**的智能指针，它保证同一时间内只有一个指针可以指向所管理的对象。

   `unique_ptr` 是类型安全的，因为它不能拷贝，只能移动所有权。当 `unique_ptr` 被销毁时，它所管理的对象也会被**自动释放**。

   使用 `unique_ptr` 可以有效避免动态分配内存的泄漏问题。

2. 示例：

   ```cpp
   #include <iostream>
   #include <memory>
   
   int main() {
       std::unique_ptr<int> uptr(new int(42));
       std::cout << *uptr << std::endl;
       return 0;
   }
   ```

3. 自己实现：

   ```cpp
   template <typename T>
   class my_unique_ptr {
   public:
       // 构造函数
       my_unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}
   
       // 禁止拷贝构造和拷贝赋值
       // = delete 指这个函数不能被调用，是 C++11 新特性，一般用来处理拷贝构造赋值之类的函数以表明禁止使用
       my_unique_ptr(const my_unique_ptr<T>&) = delete;
       my_unique_ptr<T>& operator=(const my_unique_ptr<T>&) = delete;
   
       // 移动构造函数
       my_unique_ptr(my_unique_ptr<T>&& other) : ptr_(other.release()) {}
   
       // 移动赋值运算符
       my_unique_ptr<T>& operator=(my_unique_ptr<T>&& other) {
           reset(other.release());
           return *this;
       }
   
       // 析构函数
       ~my_unique_ptr() { delete ptr_; }
   
       // 获取指针
       T* get() const { return ptr_; }
   
       // 获取指针引用
       T& operator*() const { return *ptr_; }
   
       // 获取指针成员访问
       T* operator->() const { return ptr_; }
   
       // 释放指针所有权
       T* release() {
           T* res = ptr_;
           ptr_ = nullptr;
           return res;
       }
   
       // 重置指针
       void reset(T* ptr = nullptr) {
           if (ptr_ != ptr) {
               delete ptr_;
               ptr_ = ptr;
           }
       }
   
   private:
       T* ptr_;
   };
   
   ```

   

### 11 什么是 `shared_ptr` ?

1. **是什么**

   在 C++ 中，`shared_ptr` 是一个智能指针（smart pointer），用于管理动态分配的对象。与 `unique_ptr` 不同，`shared_ptr` 允许多个智能指针共享同一个对象，当没有任何智能指针引用该对象时，该对象会自动被销毁。`shared_ptr` 基于引用计数实现，每个 `shared_ptr` 都会维护一个引用计数，记录有多少个 `shared_ptr` 共享该对象，当引用计数为零时，`shared_ptr` 会自动删除对象。

2. **怎么使用**

   在创建 `shared_ptr` 时，需要通过 `new` 关键字动态分配对象，然后将对象的指针传递给 `shared_ptr` 构造函数。当不再需要对象时，`shared_ptr` 会自动删除该对象。

3. **好处**

   使用 `shared_ptr` 可以避免内存泄漏和悬垂指针等问题，因为 `shared_ptr` 会自动管理对象的生命周期。

4. 示例：

   ```cpp
   #include <iostream>
   #include <memory>
   
   class MyClass {
   public:
       MyClass() { std::cout << "MyClass created!" << std::endl; }
       ~MyClass() { std::cout << "MyClass destroyed!" << std::endl; }
   };
   
   int main() {
       std::shared_ptr<MyClass> p1(new MyClass);
       {
           std::shared_ptr<MyClass> p2 = p1;  // 共享所有权
           std::cout << "p2 is pointing to the same object as p1" << std::endl;
       }  // p2 超出作用域，但不会销毁对象，因为 p1 仍然拥有所有权
       std::cout << "p1 is still alive!" << std::endl;
       return 0;
   }
   ```



### 12  什么是 `weak_ptr` ？

1. 是 `shared_ptr` 的一种补充，旨在解决 `shared_ptr` 的循环引用问题。`weak_ptr` 指向一个由 `shared_ptr` 管理的对象，但不会增加其引用计数，因此它并不能保证对象一直存在。`weak_ptr` 主要用于检查它指向的对象是否已被销毁，避免使用已失效的指针。
2. `weak_ptr` 通常用于解决 `shared_ptr` 可能出现的循环引用问题，即两个或多个对象相互持有 `shared_ptr`，导致引用计数永远不为零，内存无法释放。通过使用 `weak_ptr`，可以在 `shared_ptr` 之间创建一种弱关系，避免循环引用问题。



### 13 `enum class ` 和 `enum` 有什么区别？

1. `enum`的枚举值会被隐式转换为整数类型，而`enum class`的枚举值不会。

2. `enum`的作用域是其定义所在的作用域，而`enum class`的作用域是其类的作用域。

3. 示例：

   ```cpp
   enum Color {
       RED,
       GREEN,
       BLUE
   };
   // Color 中的枚举值可以隐式等价于 int
   
   enum class Animal {
       DOG,
       CAT,
       BIRD
   };
   // 不与 int 等价
   ```

### 14 `unique_ptr` 怎样转换所有权？

1. 使用 `std::move()` 将原指针转移给新指针（即移动语义），原指针会自动调用 `unique_ptr::release()` 释放。

   ```cpp
   #include <iostream>
   #include <memory>
   
   int main() {
       int* p = new int(10);
       std::unique_ptr<int> ptr1(p); // ptr1 现在拥有 p 的所有权
       std::unique_ptr<int> ptr2 = std::move(ptr1); // ptr2 获得了 p 的所有权，ptr1 失去了所有权
       std::cout << *ptr2 << std::endl; // 输出 10
       // 此时 ptr1 不再指向 p，调用 ptr1.release() 会返回 nullptr
       return 0;
   }
   ```



## STL

### 1 C++ 使用数组和 `std::array` 分别有什么优缺点？

1. **长度大小**

   数组的大小必须是编译时常量，而 `std::array` 的大小可以是**编译时常量**或**运行时变量**。

2. **安全性**

   使用 `std::array` 可以更好地避免越界访问错误，因为它具有内置的范围检查，而数组没有。

### 2 `std::vector` 最大特点是什么，与 `std::array` 相比有什么不同？

1. **大小不同**

   `std::vector`是动态数组，可以在运行时动态调整其大小，而`std::array`是静态数组，一旦创建大小就无法改变。

2. **存储方式不同**

   `std::vector`使用堆内存存储元素，而`std::array`使用栈内存存储元素。

3. **迭代器稳定性不同**

   对于`std::vector`，当容器的大小发生变化时，迭代器的指向可能会失效，而对于`std::array`，迭代器的指向不会失效。

### 3 `std::vector` 的 `resize` `reserve` `clear` 如何实现？

1. `vector.resize()` 将这个向量的长度变为指定长度，如果原向量长了就将多出来的元素删掉，如果原向量短了就使用 `0` 或者指定值补充。

   ```cpp
   std::vector<int> myvector;
   
   for (int i=1;i<10;i++) myvector.push_back(i); // [1,2,3,4,5,6,7,8,9]
   
   myvector.resize(5); // [1,2,3,4,5]
   myvector.resize(8,100); // [1,2,3,4,5,100,100,100]
   myvector.resize(12); // [1,2,3,4,5,100,100,100,0,0,0,0]
   ```

2. `vector.reserve()` 可以请求此向量至少足以包含 n 个元素。尽管 `std::vector` 在插入元素时具有动态长度的能力，但在某些情况下，预先分配一定的内存空间可能会提高 `std::vector` 的性能。

   ```cpp
   // vector::reserve
   #include <iostream>
   #include <vector>
   
   int main ()
   {
     std::vector<int>::size_type sz;
   
     // 不使用 reserve 指定容量， vector 每次扩充为原来的2倍
     std::vector<int> foo;
     sz = foo.capacity();
     std::cout << "making foo grow:\n";
     for (int i=0; i<100; ++i) {
       foo.push_back(i);
       if (sz!=foo.capacity()) {
         sz = foo.capacity();
         std::cout << "capacity changed: " << sz << '\n';
       }
     }
   
     std::vector<int> bar;
     sz = bar.capacity();
     bar.reserve(100);   // 直接使用
     std::cout << "making bar grow:\n";
     for (int i=0; i<100; ++i) {
       bar.push_back(i);
       if (sz!=bar.capacity()) {
         sz = bar.capacity();
         std::cout << "capacity changed: " << sz << '\n';
       }
     }
     return 0;
   }
   ```

   ```
   making foo grow:
   capacity changed: 1
   capacity changed: 2
   capacity changed: 4
   capacity changed: 8
   capacity changed: 16
   capacity changed: 32
   capacity changed: 64
   capacity changed: 128
   making bar grow:
   capacity changed: 100
   ```

3.  `clear()` 函数用于清空 vector 中的元素，让其 size 为 0。实现 `clear()` 可以将底层数据的元素全部析构，然后将 size 置为 0。

   ```cpp
   template <typename T>
   void vector<T>::clear() noexcept {
       for (size_t i = 0; i < m_size; ++i) {
           m_allocator.destroy(&m_data[i]); // 析构元素
       }
       m_size = 0;
   }
   ```

### 4 `std::deque` 底层数据结构是什么，内部如何实现？

1. `deque`（双端队列）是一个支持在队列两端进行高效插入和删除操作的容器，可以认为是一种动态数组和双向链表的混合体。
2. `deque` 内部的实现方式一般是采用**分块结构**，将其内部分成多个连续的内存块（chunk），**每个内存块内部是一个固定大小的数组**，双端队列内部通过指向首尾块的指针（如`begin_`和`end_`）和块内元素的索引（如`front_index`和`back_index`）来维护队列的元素。
3. 在进行插入和删除操作时，`deque` 内部会根据当前元素的位置和相对位置选择在头部或尾部的块进行操作，从而使其具有高效的插入和删除操作。同时，`deque` 还支持随机访问操作，可以通过指向块的指针和块内元素的索引快速定位到指定位置的元素。

### 5 `std::map` 和 `std::unordered_map` 区别是什么，分别在什么场景下使用？

1. `map` 底层使用 **红黑树（Red-Black Tree）** 实现，保证了元素按照键的大小有序存储，时间复杂度为  $O(log n)$ ，适用于需要快速查找、排序、遍历键值对的场景。由于红黑树的特性，`map` 内部存储的键值对是有序的，因此需要占用额外的空间来维护这种有序性。
2. `unordered_map` 底层使用 **哈希表（Hash Table）** 实现，元素的排列顺序不固定，时间复杂度为 $O(1)$ ，适用于需要快速查找、插入、删除的场景。由于哈希表的特性，`unordered_map` 内部存储的键值对是无序的，因此不需要额外的空间来维护有序性，但是在遍历键值对时需要注意顺序不固定的情况。
3. 需要根据实际需求来选择使用哪种容器。如果需要对元素进行**有序存储或查找，或者需要对键进行排序**，可以选择 `map`；如果需要**快速的插入、查找和删除**，可以选择 `unordered_map`。同时，在对存储空间的要求上，`unordered_map` 可能会占用更多的空间，因为需要存储哈希表的额外信息，而 `map` 不需要。

### 6 `std::list` 在什么场景下使用，与 `std::vector` 的区别？

1. 它使用双向链表实现。与 `vector` 或 `deque` 不同，它没有随机访问迭代器，**因此不能进行下标操作**，而是只能通过迭代器进行顺序访问。

2. `list` 的主要使用场景：

   - 需要频繁的插入或删除操作，因为在链表中这些操作的时间复杂度为 O(1)。

   - 不需要随机访问元素，因为在链表中访问元素的时间复杂度为 O(n)。

   - 不需要连续内存，因为链表的结点可以存储在不同的内存位置上。

3. 在需要随机访问元素或连续内存时，建议使用 `vector` 或 `deque`。

### 7 `std::string` 的常用方法有哪些？

1. `std::string::size()` / `std::string::length()` ：获取字符串的长度。

   ```cpp
   std::string str = "hello world";
   std::cout << str.size() << std::endl; // 输出 11
   ```

2. `std::string::substr()`：返回一个从指定位置开始的子字符串。

   ```cpp
   std::string str = "hello world";
   std::string substr = str.substr(6, 5); // 从第 6 个字符开始，取 5 个字符
   std::cout << substr << std::endl; // 输出 world
   ```

3. `std::string::find()`：查找指定字符串在当前字符串中的位置。

   ```cpp
   std::string str = "hello world";
   std::size_t pos = str.find("world"); // 查找 world 在字符串中的位置
   if (pos != std::string::npos) {
       std::cout << "found at position " << pos << std::endl;
   } else {
       std::cout << "not found" << std::endl;
   }
   ```

4. `std::string::replace()`：将指定位置的子字符串替换为另一个字符串。

   ```cpp
   std::string str = "hello world";
   str.replace(6, 5, "everyone"); // 将 world 替换为 everyone
   std::cout << str << std::endl; // 输出 hello everyone
   ```

5. `std::string::insert()`：在指定位置插入一个字符串或字符。

   ```cpp
   std::string str = "hello";
   str.insert(5, " world"); // 在 hello 之后插入 world
   std::cout << str << std::endl; // 输出 hello world
   ```

6. `std::string::c_str()`：将 string 对象转换为 C 风格的字符串。

   ```cpp
   std::string str = "hello";
   const char* cstr = str.c_str(); // 转换为 C 风格的字符串
   std::cout << cstr << std::endl; // 输出 hello
   ```

   

## Other

### 1 C++ 中栈和堆有什么区别？

1. **空间是否动态分配**

   栈空间的大小是固定的，由编译器在编译时分配，而堆空间的大小可以在运行时动态分配。

2. **是否自动分配回收**

   栈内存的分配和释放是自动的，由编译器自动完成，而堆内存的分配和释放需要程序员显式地调用相应的函数，如 `new` / `delete` 或  `malloc` / `free` 。

3. **生命周期**

   在栈上分配的变量的生命周期与所在函数的生命周期相同，当函数退出时，变量会自动被释放，而在堆上分配的变量的生命周期不受函数的限制，需要程序员自己手动释放。

4. **访问周期**

   栈空间的访问速度比堆空间更快，因为栈空间是连续的，而堆空间可能是分散的。



# C

## basic

### 1 `const` 作用是什么？

1. **防止修改**

   ```c
   const int a = 10;
   a = 5; // 错误：尝试修改常量a的值
   ```

2. **编译时优化**

   ```c
   const int a = 10;
   const int b = 20;
   int c = a + b; // 编译器在编译时将a和b的值相加，并将结果赋值给c
   ```

3. **防止函数修改参数值**

   ```c
   void foo(const int *ptr) {
       // 尝试修改ptr指向的值会导致编译错误
   }
   
   int main() {
       int a = 10;
       foo(&a); // 传递a的地址给foo，但foo不能修改a的值
       return 0;
   }
   ```

4. **增加可读性（明确不可修改）**

   ```c
   const int MAX_LENGTH = 100;
   char str[MAX_LENGTH]; // 使用有意义的常量名称代替魔法数字100
   
   const float PI = 3.14159;
   float r = 5.0;
   float area = PI * r * r; // 使用常量名称代替魔法数字3.14159
   ```

### 2 `char*` `const char*` `char* const` `const char* const` 有什么区别？

1. **`char*`**

   字符类型指针。

2. **`const char*`**

   指针可以修改，但是指向的内存区域不可修改。

3. **`char* const`**

   指针不可修改，但是指向的内存区域可以修改。

4. **`const char* const`**

   指针本身和指向的内存区域都不可修改。

5. 示例：

   ```c
   // char *
   char str[] = "hello";
   char *p = str;
   *p = 'H'; // 修改指针指向的内存区域的值
   p++; // 修改指针本身的值
   
   // const char *
   const char *p = "hello";
   p++; // 修改指针本身的值
   *p = 'H'; // 错误：不能修改指针指向的内存区域的值
   
   // char * const
   char str[] = "hello";
   char * const p = str;
   p++; // 修改指针本身的值
   *p = 'H'; // 修改指针指向的内存区域的值
   
   // const char * const
   const char * const p = "hello";
   p++; // 错误：不能修改指针本身的值
   *p = 'H'; // 错误：不能修改指针指向的内存区域的值
   ```

   

### 3 常量指针和指针常量有什么区别？

1. 区别为**指针本身和指向的内存区域是否为常量**。

2. **常量指针**

   指向内存是常量，但指针本身可变，一般是 `const T* varname` 的形式：

   ```c
   int a = 10;
   const int *p = &a;
   p++;  // 可以修改指针本身
   *p = 20; // 错误：不能修改指针指向的内存区域的值
   ```

3. **指针常量**

   指针本身是常量，指向内存内容可变，一般是 `T* const varname` 的形式：

   ```c
   int a = 10;
   int *const p = &a;
   p++; // 错误：不能修改指针本身
   *p = 20; // 可以修改指针指向的内存区域的值
   ```



### 4 `ststic` 关键字的作用和使用场景是什么？

1. **静态变量**

   `static` 关键字可以用于声明静态变量，即在函数内部定义的变量，但它的生命周期不随函数的调用而改变。静态变量只会在第一次调用该函数时被初始化，以后调用该函数时不会重新初始化。静态变量只能在声明它的函数内部使用，其他函数无法访问。

   ```c
   #include <stdio.h>
   
   void test()
   {
       static int count = 0;
       count++;
       printf("count = %d\n", count);
   }
   
   int main()
   {
       test(); // 输出 count = 1
       test(); // 输出 count = 2
       test(); // 输出 count = 3
       return 0;
   }
   ```

2. **静态函数**

   `static` 关键字也可以用于声明静态函数，即该函数只能在当前文件中被访问，其他文件无法访问。

   ```c
   // file1.c
   #include <stdio.h>
   
   static void printHello()
   {
       printf("Hello, world!\n");
   }
   
   void sayHello()
   {
       printHello();
   }
   ```

   ```c
   // file2.c
   #include <stdio.h>
   
   void sayHello(); // 声明函数，不需要包含文件 file1.h
   
   int main()
   {
       sayHello(); // 输出 Hello, world!，sayHello 不是静态函数，可以在 file2.c 访问
       // printHello() 会报错，因为 printHello 不可在 file2.c 中访问
       return 0;
   }
   ```

3. **静态全局变量**

   在函数外部定义的变量默认为全局变量，可以被程序中所有函数访问。在全局变量前加上 `static` 关键字，就变成了静态全局变量，它的作用域仅限于定义它的文件中，其他文件无法访问。

   ```c
   // file1.c
   #include <stdio.h>
   
   static int count = 0;
   
   void incrementCount()
   {
       count++;
   }
   
   void printCount()
   {
       printf("count = %d\n", count);
   }
   ```

   ```c
   // file2.c
   #include <stdio.h>
   
   void incrementCount(); // 声明函数，不需要包含文件 file1.h
   void printCount(); // 声明函数，不需要包含文件 file1.h
   
   int main()
   {
       incrementCount();
       incrementCount();
       printCount(); // 输出 count = 0
       return 0;
   }
   ```

### 5 全局变量和局部变量的区别？

1. **作用域**

   全局变量的作用域是整个程序，从定义的位置开始一直到程序结束，可以在程序中的任何地方被访问。而局部变量的作用域仅限于定义它的函数内部，只能在函数内部被访问。

2. **生命周期**

   全局变量的生命周期是整个程序，从定义的位置开始一直到程序结束。而局部变量的生命周期仅限于定义它的函数内部，在函数执行完毕后就会被销毁。

3. **初始化**

   全局变量在定义时会被自动初始化为 0 或空值，如果在定义时赋了初值，则会按照赋值进行初始化。而局部变量在定义时不会被自动初始化，需要显式地赋初值后才能使用。

4. **存储位置**

   全局变量存储在静态存储区域中，而局部变量存储在栈内存中。

5. 示例：

   ```c
   #include <stdio.h>
   
   int globalVar = 10; // 定义全局变量
   
   void test()
   {
       int localVar = 20; // 定义局部变量
       printf("globalVar = %d, localVar = %d\n", globalVar, localVar);
   }
   
   int main()
   {
       test(); // 输出 globalVar = 10, localVar = 20
       printf("globalVar = %d\n", globalVar); // 输出 globalVar = 10
       //printf("localVar = %d\n", localVar); // 编译错误，局部变量无法在函数外部访问
       return 0;
   }
   ```

   

### 6 宏定义的优缺点？

1. 宏定义使用 `#define identify value` 定义。
2. **优点**
   - 可定义常量，方便代码复用。
   - 可定义代码片段，减少代码重复。
   - 可实现条件编译，根据宏的设定编译不同代码。
3. **缺点**
   - 没有类型检查，容易出错。
   - 代码可读性下降。
   - 不能被调试器识别。
4. 因为宏定义存在以上的缺点，所以在编写 C 代码时，不建议使用宏定义，特别是用于函数或代码片段的宏定义。**可以使用 `const` 常量、枚举类型、函数、结构体**等 C 语言的其他特性来替代宏定义。

### 7 内存对齐是什么？

1. C 语言内存对齐是指在内存中分配变量时，将变量的起始地址调整为其数据类型所占内存大小的整数倍。这样做的目的是为了**提高内存读写的效率**，同时也可以避免一些硬件平台对未对齐内存的访问产生异常。

2. C 语言中的内存对齐规则可以使用 `#pragma pack` 指令来控制，其语法如下：

   ```c
   #pragma pack(n)
   ```

   其中，`n` 表示对齐方式，可以是 1、2、4、8 等，表示对齐到 1、2、4、8 等字节边界。如果不指定对齐方式，则默认按照编译器的默认对齐方式进行对齐。

3. 过多地使用内存对齐可能会降低程序的性能，因为它会**增加内存的占用和访问的次数**。因此，应该根据实际情况权衡利弊，避免滥用内存对齐。

### 8 `inline` 内联函数的特点和优缺点是什么？

1. `inline` 关键字可以用于定义内联函数，它的作用是告诉编译器在调用该函数时将其代码直接嵌入到调用处，而不是像普通函数一样通过栈来进行调用。这样做可以减少函数调用的开销，从而提高程序的执行效率。

2. **优点**

   - **减少函数调用的开销**：由于内联函数的代码直接嵌入到调用处，避免了普通函数调用的参数传递、栈帧创建和销毁等操作，从而可以减少函数调用的开销。

   - **提高程序的执行效率**：内联函数的代码可以被编译器进行优化，从而可以产生更加高效的代码。

3. **缺点**

   - **代码膨胀**：由于内联函数的代码直接嵌入到调用处，可能会导致代码量的增加，从而影响可读性和可维护性。

   - **可执行文件体积增大**：内联函数会将函数的代码嵌入到调用处，从而会增加可执行文件的体积。

   - **可能会影响缓存效果**：内联函数的代码通常比较短小，如果被频繁地调用，可能会导致缓存命中率下降，从而影响程序的执行效率。

4. 通常情况下，应该尽量避免使用过多的内联函数，特别是对于一些比较**复杂的函数，不应该使用**内联函数来代替。另外，在使用内联函数时，需要注意避免出现递归调用和函数指针等情况，因为这些情况可能会使内联函数失效。

### 9 怎样使用 C 实现 C++ 的面向对象特性（继承封装多态）？

1. **封装** 可以使用结构体和函数指针实现。

   ```c
   #include <stdio.h>
   
   // 定义一个父类结构体
   typedef struct {
       int x;
       int y;
   } Point;
   
   // 定义一个子类结构体，继承自父类
   typedef struct {
       Point point;
       int z;
   } Point3D;
   
   // 定义一个父类函数，用于打印父类结构体的数据
   void printPoint(Point *p) { 
       printf("x=%d, y=%d\n", p->x, p->y); 
   }
   
   // 定义一个子类函数，用于打印子类结构体的数据
   void printPoint3D(Point3D *p) { 
       printf("x=%d, y=%d, z=%d\n", p->point.x, p->point.y, p->z); 
   }
   
   int main() {
       // 定义一个父类对象，并调用父类函数
       Point p = {1, 2};
       printPoint(&p);
   
       // 定义一个子类对象，并调用子类函数
       Point3D p3d = {{3, 4}, 5};
       printPoint3D(&p3d);
   
       return 0;
   }
   ```

2. **封装** 可以使用结构体和函数指针实现封装。

   ```c
   #include <stdio.h>
   
   // 定义一个结构体，用于封装数据和函数指针
   typedef struct {
       // 数据成员，私有属性
       int x;
       int y;
       
       // 函数指针，公共接口
       void (*printPoint)(void *);
   } Point;
   
   // 定义一个函数，用于打印 Point 结构体的数据
   void printPoint(void *p) {
       Point *point = (Point *)p;
       printf("x=%d, y=%d\n", point->x, point->y);
   }
   
   int main() {
       // 创建 Point 对象，并设置 x 和 y 的值
       Point p = {1, 2};
   
       // 设置公共接口函数指针，指向私有函数
       p.printPoint = printPoint;
   
       // 调用公共接口函数，打印 Point 结构体的数据
       p.printPoint(&p);
   
       return 0;
   }
   ```

3. **多态** 可以使用函数指针来实现。

   ```c
   // Animal.h
   typedef struct Animal Animal;
   
   struct Animal {
       char* name;
       void (*makeSound)(Animal* animal);
   };
   
   void Animal_init(Animal* animal, char* name);
   
   // Cat.h
   typedef struct Cat Cat;
   
   struct Cat {
       Animal base;
   };
   
   void Cat_init(Cat* cat, char* name);
   
   // Dog.h
   typedef struct Dog Dog;
   
   struct Dog {
       Animal base;
   };
   
   void Dog_init(Dog* dog, char* name);
   ```

   ```c
   // Animal.c
   #include "Animal.h"
   
   void Animal_init(Animal* animal, char* name) {
       animal->name = name;
   }
   
   // Cat.c
   #include "Cat.h"
   #include <stdio.h>
   
   static void Cat_makeSound(Cat* cat) {
       printf("%s says meow\n", cat->base.name);
   }
   
   void Cat_init(Cat* cat, char* name) {
       Animal_init(&cat->base, name);
       cat->base.makeSound = (void (*)(Animal*))Cat_makeSound;
   }
   
   // Dog.c
   #include "Dog.h"
   #include <stdio.h>
   
   static void Dog_makeSound(Dog* dog) {
       printf("%s says woof\n", dog->base.name);
   }
   
   void Dog_init(Dog* dog, char* name) {
       Animal_init(&dog->base, name);
       dog->base.makeSound = (void (*)(Animal*))Dog_makeSound;
   }
   ```

   ```c
   int main() {
       Cat cat;
       Cat_init(&cat, "Tom");
       cat.base.makeSound(&cat.base);
   
       Dog dog;
       Dog_init(&dog, "Charlie");
       dog.base.makeSound(&dog.base);
   
       return 0;
   }
   ```

### 10 `memcpy` 怎么使用？怎样才能效率更高？

1. `memcpy` 可以将内存 `src` 开始后面 `n` 个字节复制到内存 `dest` 上：

   ```c
   void* memcpy(void* dest, const void* src, size_t n);
   ```

   ```c
   char src[] = "Hello, world!";
   char dest[20];
   
   memcpy(dest, src, strlen(src) + 1); // 复制 src 到 dest
   printf("%s\n", dest);
   ```

2. 对于如何使 `memcpy` 的效率更高，一般有以下几个建议：

   - 尽可能使用编译器提供的内置优化，例如 GCC 提供的 `-O2`、`-O3` 等选项。

   - 如果要复制的内存区域非常大，可以考虑使用多线程并行复制，例如使用 OpenMP 等并行编程库。

   - 如果要复制的内存区域大小不是很大，可以考虑手动编写复制函数，使用一些优化技巧，例如使用指针对齐、使用循环展开等。

3. 需要注意的是，在进行内存复制操作时，要确保源内存区域和目标内存区域不重叠，否则可能会出现意想不到的错误。可以使用 `memmove` 函数来处理重叠区域的内存复制。

### 11 `typedef` 和 `define` 区别？

1. `typedef` 是一种定义别名方式：

   ```c
   typedef int Interger;
   Interger num = 10;
   ```

   在编译时，C 编译器会将所有使用 `Integer` 的地方自动替换为 `int`，因此在运行时并没有任何性能损失。使用 `typedef` 定义别名可以让代码更加易读易懂，而且可以避免一些拼写错误。

2. `#define` 是定义宏的方式：

   ```c
   #define MAX_LEN 100
   ```

   上面的代码定义了一个名为 `MAX_NUM` 的宏，其值为 `100`。在编译时，C 编译器会将所有使用 `MAX_NUM` 的地方自动替换为 `100`，因此在运行时并没有任何性能损失。

3. 区别

   - `typedef` 定义类型别名，而 `define` 定义的是文本替换，不能定义类型别名。

   - `typedef` 只能用于定义类型别名，而 `define` 可以定义常量、函数宏、条件编译等。

   - `typedef` 定义的别名只在当**前作用域有效**，而 `define` 定义的宏在整个程序中都有效。

     ```c
     #include <stdio.h>
     #define MAX_NUM 100
     
     void foo(void) {
         typedef int my_int; // 只在 foo() 内可使用 my_int
         my_int a = 10;
         printf("a = %d\n", a);
     }
     
     int main() {
         foo();
         printf("MAX_NUM = %d\n", MAX_NUM); // 随时可以使用 MAX_NUM
         return 0;
     }
     ```

   - `typedef` 可以定义结构体、枚举等复杂类型的别名，而 `define` 不能定义这些类型的别名。

   

