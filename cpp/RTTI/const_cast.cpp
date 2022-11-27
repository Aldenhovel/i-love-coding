#include <iostream>

using namespace std;

void change(const int* pt, int n) {
	// ���ղ���Ϊ const int*����ʹ������� int* Ҳ�ᱻ��ʽת��Ϊ const int*
	int* pc;

	// �ٽ� const int* ת��Ϊ int*
	pc = const_cast<int*>(pt);
	*pc += n;
}

int main() {
	int p1 = 100;
	const int p2 = 100;
	cout << "p1: " << p1 << ", p2: " << p2 << endl;
	
	// p1 �޸ĳɹ���������Ϊ p1 �ĵ�ַ��Ȼ��Ϊ const int* ���룬���� const_cast
	// ת��Ϊ int* �����ɹ��޸�ָ��� int p1
	change(&p1, -1);

	// p2 û���޸ĳɹ���������Ϊ const_cast ֻ�ǽ�ָ��� const int* ת��Ϊ int*
	// �� ��ָ��Ķ������� const int ���������������޸�ֵ
	change(&p2, -1);
	cout << "p1: " << p1 << ", p2: " << p2 << endl;
}