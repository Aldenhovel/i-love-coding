#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void writeData(string path, vector<string> data) {
	// 将 vector<string> 逐行写入到 path 中
	ofstream fout(path.c_str());
	for (auto s : data) fout << s.c_str() << endl;;
	fout.close();
}

vector<string> readData(string path) {
	// 将 path 中的内容逐行读取整理成 vector<string> 返回
	vector<string> res;
	char tmp[100];
	ifstream fin(path.c_str());
	while (fin.getline(tmp, 100)) res.push_back(string(tmp));
	return res;
}

int main() {
	vector<string> s = {
		"hello",
		"world"
	};
	string path = "data.txt";
	writeData(path, s);

	vector<string> new_s;
	new_s = readData(path);
	for (auto s : new_s) cout << s << endl;
}