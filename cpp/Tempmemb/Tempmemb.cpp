#include <iostream>

using namespace std;

template<typename T>
class beta {
private:

	// ������Աģ�壬��Ҫ�� class һ������
	// ������Դ洢һ���������ͣ�������߷�����
	template<typename V>
	class hold {
	private:
		V val;
	public:
		hold(V v = 0) : val(v) {};
		void show() const { cout << val << endl; }
		V Value() const { return val; }
	};

	// ʹ�øոն���ĳ�Աģ�壬����� beta ��������һ�� T ��Ա��һ�� int ��Ա
	// ���ֱ�� T q; int n; �������Ե��� hold ���෽��
	hold<T> q;
	hold<int> n;

public:
	beta(T t, int i) : q(t), n(i) {};

	// ������Աģ��
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