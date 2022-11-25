#include <iostream>

using namespace std;

template<typename T>
class HasFriend {
private:
	T item;
	// ��̬���Ա���ᱻ����ʵ�������������
	// �ڳ����ʼ��ʱ��ɷ����ڴ浽�ѣ����������ʱ�ű��ͷţ�������������٣�
	// ��Ҫָ����ʼֵ������Ĭ��Ϊ 0 
	// ��Ϊ��������ʵ�������ʹ�� HasFriend<T>::ct ����ȡ
	static int ct;
public:
	// ÿ�ι���һ�� HasFriend ʵ�������Ὣ��̬���� ct +1������ʱ -1
	HasFriend(const T& i) : item(i) { ct++; }
	~HasFriend() { ct--; }
	friend void counts();
	friend void reports(HasFriend<T>& hf);
};

template<typename T>
int HasFriend<T>::ct = 0;

// ǰ���Ѿ��� counts() ��Ϊ HasFriend<T> ����Ԫ���������ܷ��� HasFriend<T>::ct ��ֵ
void counts() {
	cout << "int count: " << HasFriend<int>::ct << ";";
	cout << "double count: " << HasFriend<double>::ct << endl;
}

void reports(HasFriend<int>& hf) {
	cout << "HasFriend<int>: " << hf.item << endl;
}

void reports(HasFriend<double>& hf) {
	cout << "HasFriend<double>: " << hf.item << endl;
}

int main() {
	cout << "No objects declared: ";
	counts();

	HasFriend<int> hfInt1(10);
	cout << "hfInt1 declared: ";
	counts();

	HasFriend<int> hfInt2(10);
	cout << "hfInt2 declared: ";
	counts();

	HasFriend<double> hfDouble(10.5);
	cout << "hfDouble decleared: ";
	counts();

	// ���������ʵ��
	reports(hfInt1);
	reports(hfInt2);
	reports(hfDouble);

	hfInt1.~HasFriend();
	cout << "remove hfInt1: ";
	counts();

	return 0;
}