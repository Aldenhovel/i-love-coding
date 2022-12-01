#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void showContents(const char* path) {

	// ��ʾ�ļ�����
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

	// ׷���ļ�������Ҫ�ٴ��ļ�ʱʹ�� ios::out | ios::app ����
	ofstream fout(path, ios::out | ios::app);

	if (!fout.is_open()) {
		cerr << "Can't open " << path << " file for output" << endl;

		// exit() ��Ҫ #include <cstdlib>
		// exit��������ʱ���Ȼ�ִ����atexit()�����Ǽǵĺ�����
		// Ȼ�����һЩ�������������ͬʱˢ�� ������������ر����д򿪵������ҹر�ͨ����׼I/O����tmpfile()��������ʱ�ļ���
		// �Ա� return ��ʹ�� exit ��ȷ�ر�ʾ�����˳����򣬲�����״̬�룬���� EXIT_FAILURE EXIT_SUCCESS 
		exit(EXIT_FAILURE);
	} 
	cout << "Enter guest names (enter a blank line to quit): " << endl;
	string name;

	// �������ʱ��������
	while (getline(cin, name) && name.size() > 0) {
		fout << name << endl;
	}
	fout.close();
}

int main() {

	const char* path = "guests.txt";

	// ��ʾ��ʼ����
	showContents(path);

	// ��������
	reviseContents(path);

	// ����ʾ����
	showContents(path);
}