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
	// ����� (1, 0) �����ﱾ��Ӧ����Ҫ����ģ���Ϊ���� 1 ������ Point& ���ͣ�����C++ʹ������ʽת��
	// �� 1 ��ʽ�ص��ù��캯��ת���� Point(1) �������δ������ִ�У���Ҫ��ֹ������ʽת��������ʹ��
	// explicit �Թ��캯���������ƣ�ֻ������ʽ����

	showNewPoint(NewPoint(1));
	// showNewPoint(1) ���ٿ��ã���ʾ�����ڽ� int ת��Ϊ NewPoint �Ĺ��캯����
	// �����ֶ����� NewPoint(1) ʵ��
}