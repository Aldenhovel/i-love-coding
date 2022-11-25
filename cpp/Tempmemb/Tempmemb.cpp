#include <iostream>

using namespace std;

template<typename T>
class beta {
private:

	// 变量成员模板，需要像 class 一样定义
	// 这里可以存储一个任意类型，输出或者返回它
	template<typename V>
	class hold {
	private:
		V val;
	public:
		hold(V v = 0) : val(v) {};
		void show() const { cout << val << endl; }
		V Value() const { return val; }
	};

	// 使用刚刚定义的成员模板，这里给 beta 类设置了一个 T 成员和一个 int 成员
	// 相比直接 T q; int n; 这样可以调用 hold 的类方法
	hold<T> q;
	hold<int> n;

public:
	beta(T t, int i) : q(t), n(i) {};

	// 函数成员模板
	template<typename U>
	U blab(U u, T t) { return (n.Value() + q.Value()) * u / t; }
	void show() const { q.show(); n.show(); }

};

int main() {
	beta<double> guy(3.5, 3);
	cout << "T was set to double!" << endl;
	guy.show();
	cout << "V was set to T, double, then V was set to int." << endl;
	cout << guy.blab(10, 2.3) << endl;
	cout << "U was set to int." << endl;
	cout << guy.blab(10.0, 2.3) << endl;
	cout << "U was set to double." << endl;
	cout << "Done" << endl;
	return 0;
}