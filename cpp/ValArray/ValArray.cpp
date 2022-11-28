#include <array>
#include <valarray>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main() {

	// vector 标准容器
	// array 定长， 
	// valarray 主要面向数值计算，
	// 都不支持 push_back() pop()
	vector<double> ved1(10), ved2(10), ved3(10);
	array<double, 10> vod1, vod2, vod3;
	valarray<double> vad1(10), vad2(10), vad3(10);

	/*
		std::transform 用于 STL 容器的 mapping ，可以将一个或两个容器的内容取出来运算再放到另一个容器里
		参数 first1 -- v1.begin()
			 last1 -- v1.end()
			 first2 -- v2.begin()
			 result -- v3.begin()
			 binary_op -- 函数名，可以自己定义，如 int plusOne(int i) { return i+1; }

		一元操作原型
		template <class InputIterator, class OutputIterator, class UnaryOperation>
		OutputIterator transform (InputIterator first1, 
								  InputIterator last1,
								  OutputIterator result, 
								  UnaryOperation op);
		
		二元操作原型（有 first2）
		template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
		OutputIterator transform (InputIterator1 first1, 
								  InputIterator1 last1,
								  InputIterator2 first2, 
								  OutputIterator result,
								  BinaryOperation binary_op);
	*/

	// vector 中逐元素 ved3 = ved1 + ved2 
	transform(ved1.begin(), ved1.end(), ved2.begin(), ved3.begin(), plus<double>());
	for (auto i : ved1) { cout << i; }; cout << endl;
	for (auto i : ved2) { cout << i; }; cout << endl;
	for (auto i : ved3) { cout << i; }; cout << endl;
	// ved3 每元素自乘 10 倍，这里使用了 std::bind1st() 来将 10.0 绑定到 multiplies<double> 的第一个参数上
	// C++ 17 已经移除这种写法
	transform(ved3.begin(), ved3.end(), ved3.begin(), bind1st(multiplies<double>(), 10.0));
	for (auto i : ved1) { cout << i; }; cout << endl;
	for (auto i : ved2) { cout << i; }; cout << endl;
	for (auto i : ved3) { cout << i; }; cout << endl;



	// array 的方法与 vector 相同，因为都是标准的 STL 方法
	transform(vod1.begin(), vod1.begin(), vod2.begin(), vod3.begin(), plus<double>());


	// valarray 可以直接加
	vad3 = vad1 + vad2;
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// valarray 可以直接自乘
	vad3 *= 10.0;
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// 取 log
	vad3 = log(vad3);
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// 复杂运算时用 valarray 更直观
	vad3 = 10.0 * ((vad1 + vad2) / 2.0 + vad1 * cos(vad2));
}