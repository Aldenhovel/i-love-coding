#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

// 由于 Stack 是模板，因此所有与 Stack 有关的操作都要带上 <T>
template<typename T>
Stack<T>::Stack() {
	top = 0;
}

template<typename T>
bool Stack<T>::isempty() {
	return top == 0;
}

template<typename T>
bool Stack<T>::isfull() {
	return top == MAX;
}

template<typename T>
bool Stack<T>::push(const T &item) {
	if (top < MAX) {
		// top 指向待填充位置，比如 top=0 时第 0 位待填充
		// 因此 push 是先填充再移动
		items[top++] = item;
		return true;
	}
	else return false;
}

template<typename T>
bool Stack<T>::pop(T &item) {
	if (top > 0) {
		// pop 与 push 相反，需要先移动再弹出
		item = items[--top];
		return true;
	}
	else return false;
}

template <typename T>
AStack<T>::AStack(int ss) : stacksize(ss), top(0) {
	items = new T[stacksize];
}

template<typename T>
AStack<T>::AStack(const AStack &st) {
	stacksize = st.stacksize;
	top = st.top;
	// st 指针内容需要逐个复制过来，不能直接 items = st.items
	// 不然 st 被析构之后这个复制过来的内存也会被释放
	items = new T[stacksize];
	for (int i = 0; i < top; i++) {
		items[i] = st.items[i];
	}
}

template<typename T>
bool AStack<T>::push(const T &item) {
	if (top < stacksize) {
		items[top++] = item;
		return true;
	}
	else return false;
}

template<typename T>
bool AStack<T>::pop(T & item) {
	if (top > 0) {
		item = items[--top];
		return true;
	}
	else return false;
}

// 自我赋值，注意是有返回值的，返回 *this
template<typename T>
AStack<T>& AStack<T>::operator=(const AStack<T> & st) {
	// this 是一个 const 指针，指向实例本身，所以不能修改且实例化后才能使用
	if (this == &st) return *this;
	delete[] items;
	stacksize = this->stacksize;
	top = this->top;
	items = new T[stacksize];
	for (int i = 0; i < stacksize; i++) {
		items[i] = st.items[i];
	}
	return *this;
}

int main() {
	Stack<string> st;
	AStack<int> ast;

	ast.push(12);
	AStack<int> ast2 = ast;
	int i = 0;
	ast2.pop(i);
	cout << i << endl;
}