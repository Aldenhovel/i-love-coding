#include <iostream>
#include <fstream>
#include <string>

int main() {
	using namespace std;
	string filename;
	cout << "Enter name for new file: ";
	cin >> filename;


	// �½����ļ���д��
	// const char* string.c_str() ���Է���һ����C��ȫ���ݵ� char* ָ�룬������ string һ��
	// ��ô����Ϊ�˼����Կ��ǣ���Ϊ�ܶ�ط��������� string ���ǲ��� const char* �洢�ַ���
	ofstream fout(filename.c_str());
	fout << "For your eyes\n only!" << endl;

	cout << "Enter your secret number: " << endl;
	float secret;
	cin >> secret;
	fout << "Your secret number is: " << secret << endl;
	fout.close();


	// ��ȡ�ļ�
	ifstream fin(filename.c_str());
	cout << "Here are the contents of " << filename << ": " << endl;
	char ch;
	// ʹ�� while(fin.get(ch)) ���ȡ���а��� Space TAB Enter �����ݣ�ֱ�� EOF
	while (fin.get(ch)) cout << ch;
	cout << "Done!" << endl;
	fin.close();

	return 0;
}