#pragma once

using namespace std;

template<typename Item>
class QueueTP {
private:
	enum { Q_SIZE = 10 };

	// ����� QueueTP ������� Node ��ÿ�� Node ���洢һ�� Item ����
	// �����Ҫʹ����Ƕ�ף��Է������Դ洢������������
	class Node {
	public:
		Item item;
		Node* next;
		Node(const Item& i) : item(i), next(0) {};
	};

	// ͷβָ��
	Node* front;
	Node* rear;
	// Ԫ�ظ���
	int items;
	// ������
	const int qsize;
	QueueTP(const QueueTP& q) : qsize(0) {};
	QueueTP& operator=(const QueueTP& q) { return *this; }

public:
	QueueTP(int qs = Q_SIZE);
	~QueueTP();
	bool isempty() const { return items == 0; }
	bool isfull() const { return items == qsize; }
	int queuecount() const { return items; }

	// ��ϰ��
	// queue->front �� queue->rear ��ָ���Ѿ��洢��Ԫ�أ��������� stack.top ����һλ�ã�
	// push �� queue->rear , �� queue->front pop ���� 
	// ��ʱ���� front = rear = 0
	// һ��Ԫ��ʱ���� front = rear
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
};