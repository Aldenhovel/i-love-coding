#include <iostream>

using namespace std;

template<typename T>
class HasFriend {
private:
	T item;
	// 静态类成员，会被所有实例化的类对象共享
	// 在程序初始化时完成分配内存到堆，到程序结束时才被释放（不会随对象销毁）
	// 需要指定初始值，否则默认为 0 
	// 因为属于所有实例，因此使用 HasFriend<T>::ct 来获取
	static int ct;
public:
	// 每次构造一个 HasFriend 实例，都会将静态变量 ct +1，销毁时 -1
	HasFriend(const T& i) : item(i) { ct++; }
	~HasFriend() { ct--; }
	friend void counts();
	friend void reports(HasFriend<T>& hf);
};

template<typename T>
int HasFriend<T>::ct = 0;

// 前面已经将 counts() 作为 HasFriend<T> 的友元，这样才能访问 HasFriend<T>::ct 的值
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

	// 检查这三个实例
	reports(hfInt1);
	reports(hfInt2);
	reports(hfDouble);

	hfInt1.~HasFriend();
	cout << "remove hfInt1: ";
	counts();

	return 0;
}