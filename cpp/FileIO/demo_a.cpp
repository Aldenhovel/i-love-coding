#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void showContents(const char* path) {

	// 显示文件内容
	char ch;
	ifstream fin;
	fin.open(path);
	if (fin.is_open()) {
		cout << "Here are the contents of the " << path << " file: " << endl;
		while (fin.get(ch)) cout << ch;
		fin.close();
	}
}

void reviseContents(const char* path) {

	// 追加文件内容需要再打开文件时使用 ios::out | ios::app 参数
	ofstream fout(path, ios::out | ios::app);

	if (!fout.is_open()) {
		cerr << "Can't open " << path << " file for output" << endl;

		// exit() 需要 #include <cstdlib>
		// exit函数运行时首先会执行由atexit()函数登记的函数，
		// 然后会做一些自身的清理工作，同时刷新 所有输出流、关闭所有打开的流并且关闭通过标准I/O函数tmpfile()创建的临时文件。
		// 对比 return ，使用 exit 明确地表示当即退出程序，并返回状态码，包括 EXIT_FAILURE EXIT_SUCCESS 
		exit(EXIT_FAILURE);
	} 
	cout << "Enter guest names (enter a blank line to quit): " << endl;
	string name;

	// 输入空行时结束输入
	while (getline(cin, name) && name.size() > 0) {
		fout << name << endl;
	}
	fout.close();
}

int main() {

	const char* path = "guests.txt";

	// 显示初始内容
	showContents(path);

	// 新增内容
	reviseContents(path);

	// 再显示内容
	showContents(path);
}