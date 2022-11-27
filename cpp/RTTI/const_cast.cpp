#include <iostream>

using namespace std;

void change(const int* pt, int n) {
	// 接收参数为 const int*，即使传入的是 int* 也会被隐式转换为 const int*
	int* pc;

	// 再将 const int* 转化为 int*
	pc = const_cast<int*>(pt);
	*pc += n;
}

int main() {
	int p1 = 100;
	const int p2 = 100;
	cout << "p1: " << p1 << ", p2: " << p2 << endl;
	
	// p1 修改成功，这是因为 p1 的地址虽然作为 const int* 传入，但被 const_cast
	// 转化为 int* ，并成功修改指向的 int p1
	change(&p1, -1);

	// p2 没有修改成功，这是因为 const_cast 只是将指针从 const int* 转化为 int*
	// 但 它指向的对象仍是 const int ，编译器不允许修改值
	change(&p2, -1);
	cout << "p1: " << p1 << ", p2: " << p2 << endl;
}