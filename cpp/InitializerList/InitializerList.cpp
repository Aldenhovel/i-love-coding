#include <iostream>
#include <initializer_list>

double sum(std::initializer_list<double> lst) {
	double tot = 0;
	for (auto p = lst.begin(); p != lst.end(); p++) {
		tot += *p;
	}
	return tot;
}

double average(std::initializer_list<double> lst) {
	double tot = 0;
	int n = lst.size();
	double avg = 0.0;
	if (n > 0) {
		for (auto p = lst.begin(); p != lst.end(); p++) {
			tot += *p;
		}
		avg = tot / n;
	}
	return avg;
}

int main() {
	using std::cout;
	using std::endl;

	// { ... } 代表 initializer_list 字面量，因此直接传入 initializer_list 字面量或者
	// initializer_list 变量都行，但需要注意 initializer_list::iterator 为 const 不能修改
	cout << "List 1: sum = " << sum({ 2, 3, 4 })
		<< " , avg = " << average({ 2,3,4 }) << endl;

	std::initializer_list<double> dl = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	cout << "List 2: sum = " << sum(dl)
		<< " , avg = " << average(dl) << endl;

	// 这里是将一个 initializer_list 赋给另外一个，没有问题
	dl = { 16.0, 25.0, 36.0, 40.0, 64.0 };
	cout << "List 3: sum = " << sum(dl)
		<< " , avg = " << average(dl) << endl;

}

/*
	List 1: sum = 9 , avg = 3
	List 2: sum = 16.5 , avg = 3.3
	List 3: sum = 181 , avg = 36.2
*/