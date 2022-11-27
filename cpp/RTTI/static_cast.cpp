#include <iostream>

int main(){

    int n = -1;
    char ch = 'a';
    double dle = 0.1;

    // 使用 C 风格的隐式转换
    dle = n;

    // C++ 中使用 static_cast<> 来完成隐式转换
    // 更加友好、会执行运行时检查
    dle = static_cast<double>(n);
    n = static_cast<int>(ch);

    std::cout << dle << std::endl; //-1
    std::cout << n << std::endl;  //97
    return 0;
}

