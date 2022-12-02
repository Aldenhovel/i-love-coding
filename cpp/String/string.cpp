#include <iostream>
#include <string>

using namespace std;

int main() {

	// ���캯��
	string s1();  // si = ""
	string s2("Hello");  // s2 = "Hello"
	string s3(4, 'K');  // s3 = "KKKK"
	string s4("12345", 1, 3);  //s4 = "234"���� "12345" �Ĵ��±� 1 ��ʼ������Ϊ 3 ���Ӵ�

	// ����
	cout << s2.length() << s2.size() << endl;

	// ʹ�� + ƴ�ӣ���Ҫ��������һ���� string
	// Ҳ����ʹ�� .append() ƴ��
	string s5 = "123" + string("456");
	string s6 = string("789").append("10");
	cout << s5 << endl;
	cout << s6 << endl;
	
	// ʹ�� .compare �ԱȽ����� string ���൱�����ַ��Ƚ� char �� ASCII �룬�᷵�� -1, 0, 1
	// ʹ�� ._Equal ���Ƚ����� string �Ƿ���ͬ��ֻ���� 0, 1���� .compare Ҳ����ʵ�֣�
	string s7 = "aaa";
	cout << s7.compare(string("aaa")) << endl;
	cout << s7._Equal(string("aa")) << endl;

	// ���������ַ���
	string s8 = "AA";
	string s9 = "BB";
	s8.swap(s9);
	cout << s8 << s9 << endl;

	string s10("ABCDEABCDE");
	int n;
	// �����ִ����ֵ�λ�ã��Ҳ����᷵�� string::npos ������� 0 �� -1 ��Ҫע��
	if ((n = s10.find("CDE")) != string::npos) cout << "pos: " << n << endl;
	// ��ĳλ�ÿ�ʼ��
	if ((n = s10.find("CDE", 1)) != string::npos) cout << "pos: " << n << endl;
	// �ҵ�һ�γ���λ��
	if ((n = s10.find_first_of("ABC")) != string::npos) cout << "pos: " << n << endl;
	// �����һ�γ���λ��
	if ((n = s10.find_last_of('ABC')) != string::npos) cout << "pos: " << n << endl;

	// ��ȡ�ִ�
	string s11 = "ABCDE";
	cout << s11.substr(1, 3) << endl;	// ���±� 1 ��ʼ���ִ�����Ϊ 3

	// �û��ִ������У�
	// ԭ��Ϊ string.replace(pos, old_size, new_str) ����Ҫ�û��ض�λ�õ����� find/find_first_of/find_last_of �ҳ���
	string s12 = "ABCDEABCDE";
	string oldstr = "BCD";
	string newstr = "XXXYYYZZZ";
	while ((n = s12.find(oldstr)) != string::npos) s12.replace(n, oldstr.size(), newstr);
	cout << s12 << endl;

	// ɾ���ִ�
	string s13 = "ABCDEABCDE";
	cout << s13.erase(1, 3) << endl;	// �±� 1 ��ʼɾ��ɾ 3 ���ַ�
	cout << s13.erase(1) << endl;		// �±� 1 �����ȫ��ɾ��

	// �м����
	string s14 = "AA";
	cout << s14.insert(1, "B") << endl;

	// ͨ�� STL ��ʽ���������Կ��������� char ���
	string s15 = "ABCDE";
	for (string::iterator p = s15.begin(); p != s15.end(); p++) cout << *p << " is " << typeid(*p).name() << endl;

}