#include <iostream>
#include <valarray>
#include <cstdlib>

const int SIZE = 12;

typedef std::valarray<int> vint;

void show(const vint& v, int cols) {
	using std::cout;
	using std::endl;

	int lim = v.size();
	for (int i = 0; i < lim; ++i) {
		cout.width(3);
		cout << v[i];
		if (i % cols == cols - 1) cout << endl;
		else cout << ' ';
	}
	if (lim % cols != 0) cout << endl;
}

int main() {
	using std::slice;
	using std::cout;
	using std::endl;

	// ��ʼ��һ�� 12 λ�� valarray ��������ÿ�� 3 ���ĸ�ʽ���
	vint valint(SIZE);
	int i;
	for (i = 0; i < SIZE; ++i) {
		valint[i] = std::rand() % 10;
	}
	cout << "Original array:" << endl;
	show(valint, 3);

	// ����ڶ���
	/*
	*	valarray ���Խ��� std::slice ����Ƭ����
	*	slice(begin, size, step) ����һ����Ƭ��
	*	��ʼλ��Ԫ�ظ����Ϳ�ȡ�
	*/
	vint vcol(valint[slice(1, 4, 3)]);
	cout << "2nd col:" << endl;
	show(vcol, 1);

	// �ڶ���
	vint vrow(valint[slice(3, 3, 1)]);
	cout << "2nd row:" << endl;
	show(vrow, 3);

	// ������иĳ� 10
	valint[slice(2, 4, 3)] = 10;
	cout << "Set last column to 10:" << endl;
	show(valint, 3);

	// ����Ƭ�����㣬��Ҫ��ת��Ϊ valarray
	valint[slice(0, 4, 3)] = vint(valint[slice(1, 4, 3)]) + vint(valint[slice(2, 4, 3)]);
	cout << "Set col0 = col1 + col2:" << endl;
	show(valint, 3);
	return 0;
}