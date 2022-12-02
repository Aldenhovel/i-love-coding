#include <iostream>

using namespace std;

double betsy(int lns) {
	// Betsy д lns �д�����Ҫ���ѵ�ʱ��
	return 0.05 * lns;
}

double pam(int lns) {
	// Pam д lns �д�����Ҫ���ѵ�ʱ��
	return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*pf)(int)) {
	// ����һ������ָ�룬ע��Ҫ���Ϸ�������
	cout << lines << " lines wil take ";
	cout << (*pf)(lines) << " hour(s)" << endl;		// ����ʹ�� (*pf)()lines �� pf(lines) ������
}

int main() {
	int code;
	cout << "How many lines of code do you need? ";
	cin >> code;
	cout << "Betsy's estimate: " << endl;
	// ֱ�Ӻ�������ʾ��ַ��������ת��Ϊ����ָ��
	estimate(code, betsy);
	cout << "Pam's estimate: " << endl;
	estimate(code, pam);
	return 0;
}

/*
* �����������һ������ָ�룬Ȼ�󽫺�����ֵ�������磺
* 
* double betsy(int lns);
* double (*pf)(int);
* pf = betsy;
* 
*/
