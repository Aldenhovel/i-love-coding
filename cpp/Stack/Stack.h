#pragma once
#include <iostream>

using namespace std;

/*
	typedef unsigned long Item;

	// 不使用类模板的 Stack 类，需要使用 typedef 确定类型
	class Stack {
	private:
		enum {MAX = 10};
		Item Items[MAX];
		int top;
	public:
		Stack();
		bool isempty() const;
		bool isfull() const;

		// push 操作在成功时返回 true ，失败返回 false（比如说栈满）
		bool push(const Item &item);

		// pop 同理，成功返回 true ，栈空时返回 false ，将元素 pop 到参数 item 里面
		bool pop(Item &item);
	};
*/	


// 使用类模板
template<typename T>
class Stack {
private:
	enum { MAX = 10 };
	T items[MAX];
	int top;
public:
	Stack();
	bool isempty();
	bool isfull();
	bool push(const T &item);
	bool pop(T &item);
};


// 使用指针来管理 items ，这样可以让栈大小可变
// 其次是补充了显式构造函数、复制构造函数
template<typename T>
class AStack {
private:
	enum {SIZE = 10};
	int stacksize;
	T *items;
	int top;
public:
	explicit AStack(int ss=SIZE);
	AStack(const AStack &s);
	~AStack() { delete[] items; }
	bool isempty() { return top == 0; }
	bool isfull() { return top == stacksize; }
	bool push(const T &item);
	bool pop(T &item);
	AStack& operator=(const AStack &st);
};