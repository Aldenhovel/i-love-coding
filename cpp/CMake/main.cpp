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