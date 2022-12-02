#include <iostream>
#include <string>

using namespace std;

int main() {

	// 构造函数
	string s1();  // si = ""
	string s2("Hello");  // s2 = "Hello"
	string s3(4, 'K');  // s3 = "KKKK"
	string s4("12345", 1, 3);  //s4 = "234"，即 "12345" 的从下标 1 开始，长度为 3 的子串

	// 长度
	cout << s2.length() << s2.size() << endl;

	// 使用 + 拼接，需要两端至少一端是 string
	// 也可以使用 .append() 拼接
	string s5 = "123" + string("456");
	string s6 = string("789").append("10");
	cout << s5 << endl;
	cout << s6 << endl;
	
	// 使用 .compare 以比较两个 string ，相当于逐字符比较 char 的 ASCII 码，会返回 -1, 0, 1
	// 使用 ._Equal 来比较两个 string 是否相同，只返回 0, 1（用 .compare 也可以实现）
	string s7 = "aaa";
	cout << s7.compare(string("aaa")) << endl;
	cout << s7._Equal(string("aa")) << endl;

	// 交换两个字符串
	string s8 = "AA";
	string s9 = "BB";
	s8.swap(s9);
	cout << s8 << s9 << endl;

	string s10("ABCDEABCDE");
	int n;
	// 查找字串出现的位置，找不到会返回 string::npos 这个不是 0 或 -1 需要注意
	if ((n = s10.find("CDE")) != string::npos) cout << "pos: " << n << endl;
	// 从某位置开始找
	if ((n = s10.find("CDE", 1)) != string::npos) cout << "pos: " << n << endl;
	// 找第一次出现位置
	if ((n = s10.find_first_of("ABC")) != string::npos) cout << "pos: " << n << endl;
	// 找最后一次出现位置
	if ((n = s10.find_last_of('ABC')) != string::npos) cout << "pos: " << n << endl;

	// 截取字串
	string s11 = "ABCDE";
	cout << s11.substr(1, 3) << endl;	// 从下标 1 开始，字串长度为 3

	// 置换字串（所有）
	// 原型为 string.replace(pos, old_size, new_str) ，需要置换特定位置的先用 find/find_first_of/find_last_of 找出来
	string s12 = "ABCDEABCDE";
	string oldstr = "BCD";
	string newstr = "XXXYYYZZZ";
	while ((n = s12.find(oldstr)) != string::npos) s12.replace(n, oldstr.size(), newstr);
	cout << s12 << endl;

	// 删除字串
	string s13 = "ABCDEABCDE";
	cout << s13.erase(1, 3) << endl;	// 下标 1 开始删，删 3 个字符
	cout << s13.erase(1) << endl;		// 下标 1 后面的全部删掉

	// 中间插入
	string s14 = "AA";
	cout << s14.insert(1, "B") << endl;

	// 通过 STL 方式遍历，可以看到它是由 char 组成
	string s15 = "ABCDE";
	for (string::iterator p = s15.begin(); p != s15.end(); p++) cout << *p << " is " << typeid(*p).name() << endl;

}