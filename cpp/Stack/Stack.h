#pragma once
#include <iostream>

using namespace std;

/*
	typedef unsigned long Item;

	// ��ʹ����ģ��� Stack �࣬��Ҫʹ�� typedef ȷ������
	class Stack {
	private:
		enum {MAX = 10};
		Item Items[MAX];
		int top;
	public:
		Stack();
		bool isempty() const;
		bool isfull() const;

		// push �����ڳɹ�ʱ���� true ��ʧ�ܷ��� false������˵ջ����
		bool push(const Item &item);

		// pop ͬ���ɹ����� true ��ջ��ʱ���� false ����Ԫ�� pop ������ item ����
		bool pop(Item &item);
	};
*/	


// ʹ����ģ��
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


// ʹ��ָ�������� items ������������ջ��С�ɱ�
// ����ǲ�������ʽ���캯�������ƹ��캯��
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