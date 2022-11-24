#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

// ���� Stack ��ģ�壬��������� Stack �йصĲ�����Ҫ���� <T>
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
		// top ָ������λ�ã����� top=0 ʱ�� 0 λ�����
		// ��� push ����������ƶ�
		items[top++] = item;
		return true;
	}
	else return false;
}

template<typename T>
bool Stack<T>::pop(T &item) {
	if (top > 0) {
		// pop �� push �෴����Ҫ���ƶ��ٵ���
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
	// st ָ��������Ҫ������ƹ���������ֱ�� items = st.items
	// ��Ȼ st ������֮��������ƹ������ڴ�Ҳ�ᱻ�ͷ�
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

// ���Ҹ�ֵ��ע�����з���ֵ�ģ����� *this
template<typename T>
AStack<T>& AStack<T>::operator=(const AStack<T> & st) {
	// this ��һ�� const ָ�룬ָ��ʵ���������Բ����޸���ʵ���������ʹ��
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