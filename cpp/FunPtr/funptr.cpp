#include <iostream>

using namespace std;

double betsy(int lns) {
	// Betsy 写 lns 行代码需要花费的时间
	return 0.05 * lns;
}

double pam(int lns) {
	// Pam 写 lns 行代码需要花费的时间
	return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*pf)(int)) {
	// 接受一个函数指针，注意要带上返回类型
	cout << lines << " lines wil take ";
	cout << (*pf)(lines) << " hour(s)" << endl;		// 这里使用 (*pf)()lines 和 pf(lines) 都可以
}

int main() {
	int code;
	cout << "How many lines of code do you need? ";
	cin >> code;
	cout << "Betsy's estimate: " << endl;
	// 直接函数名表示地址，即可以转化为函数指针
	estimate(code, betsy);
	cout << "Pam's estimate: " << endl;
	estimate(code, pam);
	return 0;
}

/*
* 此外可以声明一个函数指针，然后将函数赋值给它，如：
* 
* double betsy(int lns);
* double (*pf)(int);
* pf = betsy;
* 
*/
