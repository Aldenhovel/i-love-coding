#include <iostream>

using namespace std;

// without explicit
class Point {
public:
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {};
};

// with explicit
class NewPoint {
public:
	int x, y;
	explicit NewPoint(int x = 0, int y = 0) :x(x), y(y) {};
};

void showPoint(const Point &p) {
	cout << "(" << p.x << "," << p.y << ")" << endl;
}

void showNewPoint(const NewPoint &np) {
	cout << "(" << np.x << "," << np.y << ")" << endl;
}

int main() {
	showPoint(1);
	// 输出了 (1, 0) ，这里本来应该是要报错的，因为参数 1 并不是 Point& 类型，但是C++使用了隐式转换
	// 将 1 隐式地调用构造函数转换成 Point(1) ，因此这段代码可以执行，想要防止这种隐式转换，必须使用
	// explicit 对构造函数进行限制，只允许显式调用

	showNewPoint(NewPoint(1));
	// showNewPoint(1) 不再可用，提示不存在将 int 转换为 NewPoint 的构造函数，
	// 必须手动构造 NewPoint(1) 实例
}