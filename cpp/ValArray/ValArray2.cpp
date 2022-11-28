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

	// 初始化一个 12 位的 valarray ，并且以每行 3 个的格式输出
	vint valint(SIZE);
	int i;
	for (i = 0; i < SIZE; ++i) {
		valint[i] = std::rand() % 10;
	}
	cout << "Original array:" << endl;
	show(valint, 3);

	// 输出第二列
	/*
	*	valarray 可以接受 std::slice 来切片操作
	*	slice(begin, size, step) 定义一个切片的
	*	起始位，元素个数和跨度。
	*/
	vint vcol(valint[slice(1, 4, 3)]);
	cout << "2nd col:" << endl;
	show(vcol, 1);

	// 第二行
	vint vrow(valint[slice(3, 3, 1)]);
	cout << "2nd row:" << endl;
	show(vrow, 3);

	// 将最后列改成 10
	valint[slice(2, 4, 3)] = 10;
	cout << "Set last column to 10:" << endl;
	show(valint, 3);

	// 对切片做运算，需要先转化为 valarray
	valint[slice(0, 4, 3)] = vint(valint[slice(1, 4, 3)]) + vint(valint[slice(2, 4, 3)]);
	cout << "Set col0 = col1 + col2:" << endl;
	show(valint, 3);
	return 0;
}