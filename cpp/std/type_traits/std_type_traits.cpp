#include <iostream>
#include <type_traits>

template <typename T, typename U>
struct decay_equiv: std::is_same<typename std::decay<T>::type, U>::type {};

int main() {
    std::cout << std::is_same<int&&, int>::type::type::value <<std::endl;
}
