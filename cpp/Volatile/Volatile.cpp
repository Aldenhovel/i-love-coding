#include <iostream>

// 在 C/C++ 编程语言中，volatile 的易变性体现在：假设有读、写两条语句，
// 依次对同一个 volatile 变量进行操作，那么后一条的读操作不会直接使用前
// 一条的写操作对应的 volatile 变量的寄存器内容，而是重新从内存中读取该 volatile 变量的值。
void fn1() {
	volatile int nNum = 0;  // 将nNum声明为volatile
	int nSum = 0;
	nNum = FunA();      // nNum被写入的新内容，其值会缓存在寄存器中
	nSum = nNum + 1;    // 此处会从内存（而非寄存器）中读取nNum的值
}

// 在 C/C++ 编程语言中，volatile 的第二个特性是“不可优化性”。volatile 会
// 告诉编译器，不要对 volatile 声明的变量进行各种激进的优化（甚至将变量直
// 接消除），从而保证程序员写在代码中的指令一定会被执行。
void fn2() {
	volatile int nNum;  // 将nNum声明为volatile
	nNum = 1;
	std::cout << "nNum is: " << nNum << std::endl;
}

int main() {
	fn1();
	fn2();
}