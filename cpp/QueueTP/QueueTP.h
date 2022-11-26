#pragma once

using namespace std;

template<typename Item>
class QueueTP {
private:
	enum { Q_SIZE = 10 };

	// 在这个 QueueTP 里面管理 Node ，每个 Node 都存储一个 Item 类型
	// 因此需要使用类嵌套，以泛化可以存储任意数据类型
	class Node {
	public:
		Item item;
		Node* next;
		Node(const Item& i) : item(i), next(0) {};
	};

	// 头尾指针
	Node* front;
	Node* rear;
	// 元素个数
	int items;
	// 总容量
	const int qsize;
	QueueTP(const QueueTP& q) : qsize(0) {};
	QueueTP& operator=(const QueueTP& q) { return *this; }

public:
	QueueTP(int qs = Q_SIZE);
	~QueueTP();
	bool isempty() const { return items == 0; }
	bool isfull() const { return items == qsize; }
	int queuecount() const { return items; }

	// 复习：
	// queue->front 和 queue->rear 都指向已经存储的元素（而不是像 stack.top 在下一位置）
	// push 到 queue->rear , 从 queue->front pop 出来 
	// 空时，有 front = rear = 0
	// 一个元素时，有 front = rear
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
};