#include "QueueTP.h"
#include <iostream>
#include <string>

template<typename Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs) {
	// 指针赋值 0 相当于 null
	// 因为地址 0x00 是保留地址 
	front = rear = 0;
	items = 0;
}

template<typename Item>
QueueTP<Item>::~QueueTP() {
	// 存储的指针需要遍历释放，使用 delete 释放指针内存
	Node* temp;
	while (front != 0) {
		temp = front;
		front = front->next;
		delete temp;
	}
}

// queue 至少有一个节点时， push 需要新建一个节点，然后连接到 rear->next ，最后后移 rear 
// 如果 queue 空，即 front = rear = 0 时，需要让 front = rear = 新节点
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

// pop 是将 front 指向位置的元素 pop 出来，然后将 front 向后移动（如果只有一个节点也适用，因为 node->next=0）
// 如果是只有一个节点，被 pop 出后需要修改 rear 让它指向 0

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
		// 多行字符串
		cout << "Please enter your name."
			"You will be served in the order of arrival.\n"
			"name: ";
		// 接受 string 使用 getline(cin, temp);
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