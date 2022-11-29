#include <iostream>
#include <fstream>
#include <string>

int main() {
	using namespace std;
	string filename;
	cout << "Enter name for new file: ";
	cin >> filename;


	// 新建该文件并写入
	// const char* string.c_str() 可以返回一个与C完全兼容的 char* 指针，内容与 string 一样
	// 这么做是为了兼容性考虑，因为很多地方并不适用 string 而是采用 const char* 存储字符串
	ofstream fout(filename.c_str());
	fout << "For your eyes\n only!" << endl;

	cout << "Enter your secret number: " << endl;
	float secret;
	cin >> secret;
	fout << "Your secret number is: " << secret << endl;
	fout.close();


	// 读取文件
	ifstream fin(filename.c_str());
	cout << "Here are the contents of " << filename << ": " << endl;
	char ch;
	// 使用 while(fin.get(ch)) 会读取所有包括 Space TAB Enter 的内容，直到 EOF
	while (fin.get(ch)) cout << ch;
	cout << "Done!" << endl;
	fin.close();

	return 0;
}