#include <iostream>

// �� C/C++ ��������У�volatile ���ױ��������ڣ������ж���д������䣬
// ���ζ�ͬһ�� volatile �������в�������ô��һ���Ķ���������ֱ��ʹ��ǰ
// һ����д������Ӧ�� volatile �����ļĴ������ݣ��������´��ڴ��ж�ȡ�� volatile ������ֵ��
void fn1() {
	volatile int nNum = 0;  // ��nNum����Ϊvolatile
	int nSum = 0;
	nNum = FunA();      // nNum��д��������ݣ���ֵ�Ỻ���ڼĴ�����
	nSum = nNum + 1;    // �˴�����ڴ棨���ǼĴ������ж�ȡnNum��ֵ
}

// �� C/C++ ��������У�volatile �ĵڶ��������ǡ������Ż��ԡ���volatile ��
// ���߱���������Ҫ�� volatile �����ı������и��ּ������Ż�������������ֱ
// �����������Ӷ���֤����Աд�ڴ����е�ָ��һ���ᱻִ�С�
void fn2() {
	volatile int nNum;  // ��nNum����Ϊvolatile
	nNum = 1;
	std::cout << "nNum is: " << nNum << std::endl;
}

int main() {
	fn1();
	fn2();
}