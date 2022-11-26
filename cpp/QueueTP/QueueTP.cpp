#include "QueueTP.h"
#include <iostream>
#include <string>

template<typename Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs) {
	// ָ�븳ֵ 0 �൱�� null
	// ��Ϊ��ַ 0x00 �Ǳ�����ַ 
	front = rear = 0;
	items = 0;
}

template<typename Item>
QueueTP<Item>::~QueueTP() {
	// �洢��ָ����Ҫ�����ͷţ�ʹ�� delete �ͷ�ָ���ڴ�
	Node* temp;
	while (front != 0) {
		temp = front;
		front = front->next;
		delete temp;
	}
}

// queue ������һ���ڵ�ʱ�� push ��Ҫ�½�һ���ڵ㣬Ȼ�����ӵ� rear->next �������� rear 
// ��� queue �գ��� front = rear = 0 ʱ����Ҫ�� front = rear = �½ڵ�
template<typename Item>
bool QueueTP<Item>::enqueue(const Item& item) {
	if (isfull()) return false;
	Node* add = new Node(item);
	items++;
	if (front == 0) {
		front = add;
	}
	else {
		rear->next = add;
	}
	rear = add;
	return true;
}

// pop �ǽ� front ָ��λ�õ�Ԫ�� pop ������Ȼ�� front ����ƶ������ֻ��һ���ڵ�Ҳ���ã���Ϊ node->next=0��
// �����ֻ��һ���ڵ㣬�� pop ������Ҫ�޸� rear ����ָ�� 0

template<typename Item>
bool QueueTP<Item>::dequeue(Item& item) {
	if (front == 0) return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (isempty()) rear = 0;
	return true;
}

int main() {
	// 5 computer science students
	QueueTP<string> cs(5);
	string temp;

	while (!cs.isfull()) {
		// �����ַ���
		cout << "Please enter your name."
			"You will be served in the order of arrival.\n"
			"name: ";
		// ���� string ʹ�� getline(cin, temp);
		getline(cin, temp);
		cs.enqueue(temp);
	}
	cout << "The queue is full. Processing begins ... \n";
	while (!cs.isempty()) {
		cs.dequeue(temp);
		cout << "Now processing " << temp << " ... \n";
	}
	return 0;
}