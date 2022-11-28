#include <array>
#include <valarray>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main() {

	// vector ��׼����
	// array ������ 
	// valarray ��Ҫ������ֵ���㣬
	// ����֧�� push_back() pop()
	vector<double> ved1(10), ved2(10), ved3(10);
	array<double, 10> vod1, vod2, vod3;
	valarray<double> vad1(10), vad2(10), vad3(10);

	/*
		std::transform ���� STL ������ mapping �����Խ�һ������������������ȡ���������ٷŵ���һ��������
		���� first1 -- v1.begin()
			 last1 -- v1.end()
			 first2 -- v2.begin()
			 result -- v3.begin()
			 binary_op -- �������������Լ����壬�� int plusOne(int i) { return i+1; }

		һԪ����ԭ��
		template <class InputIterator, class OutputIterator, class UnaryOperation>
		OutputIterator transform (InputIterator first1, 
								  InputIterator last1,
								  OutputIterator result, 
								  UnaryOperation op);
		
		��Ԫ����ԭ�ͣ��� first2��
		template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
		OutputIterator transform (InputIterator1 first1, 
								  InputIterator1 last1,
								  InputIterator2 first2, 
								  OutputIterator result,
								  BinaryOperation binary_op);
	*/

	// vector ����Ԫ�� ved3 = ved1 + ved2 
	transform(ved1.begin(), ved1.end(), ved2.begin(), ved3.begin(), plus<double>());
	for (auto i : ved1) { cout << i; }; cout << endl;
	for (auto i : ved2) { cout << i; }; cout << endl;
	for (auto i : ved3) { cout << i; }; cout << endl;
	// ved3 ÿԪ���Գ� 10 ��������ʹ���� std::bind1st() ���� 10.0 �󶨵� multiplies<double> �ĵ�һ��������
	// C++ 17 �Ѿ��Ƴ�����д��
	transform(ved3.begin(), ved3.end(), ved3.begin(), bind1st(multiplies<double>(), 10.0));
	for (auto i : ved1) { cout << i; }; cout << endl;
	for (auto i : ved2) { cout << i; }; cout << endl;
	for (auto i : ved3) { cout << i; }; cout << endl;



	// array �ķ����� vector ��ͬ����Ϊ���Ǳ�׼�� STL ����
	transform(vod1.begin(), vod1.begin(), vod2.begin(), vod3.begin(), plus<double>());


	// valarray ����ֱ�Ӽ�
	vad3 = vad1 + vad2;
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// valarray ����ֱ���Գ�
	vad3 *= 10.0;
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// ȡ log
	vad3 = log(vad3);
	for (auto i : vad1) { cout << i; }; cout << endl;
	for (auto i : vad2) { cout << i; }; cout << endl;
	for (auto i : vad3) { cout << i; }; cout << endl;
	// ��������ʱ�� valarray ��ֱ��
	vad3 = 10.0 * ((vad1 + vad2) / 2.0 + vad1 * cos(vad2));
}