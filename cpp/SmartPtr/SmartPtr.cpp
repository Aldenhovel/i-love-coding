#include <iostream>
#include <string>

// ����ָ����Ҫ���� <memery> ������ namespace std ��
#include <memory>

using namespace std;

class Report {
private:
	string str;
public:
	Report(const string s) : str(s) { cout << "Object created!" << endl; }
	~Report() { cout << "Object deleted!" << endl; }
	void comment() const { cout << str << endl; }
};

int main() {

	// ����ָ����� auto_ptr<T> shared_ptr<T> unique_ptr<T> ֻ�����ڱ������
	// ���ں�ᱻ�ƶ��ͷţ������ֶ� delete
	{
		auto_ptr<Report> ps(new Report("using auto_ptr"));
		ps->comment();
	}

	{
		shared_ptr<Report> ps(new Report("using shared_ptr"));
		ps->comment();
	}

	{
		unique_ptr<Report> ps(new Report("using unique_ptr"));
		ps->comment();
	}

	cout << "************************************************" << endl;

	// auto_ptr shared_ptr unique_ptr ��ʹ������
	// ��������ָ��ᱻ�Զ��ͷţ����Ե����ָ��ָ��ͬһ��ַʱ�п��ܻ����
	// ͬһ����ַ����� delete �������������Ҫ�� auto shared unique

	// ʹ�� auto_ptr ���������ʱ������Ϊ films[1] �Ѿ��������ͷŸ��� pwin
	// ��ʹ�� films[1] ʱ�����ǿ�ָ�룬����
	// ʹ�� shared_ptr �����������У���Ϊ����ͳ�Ƶ�����ָ�붼�ͷź�� delete ����
	// ʹ�� unique_ptr ���ڱ���ʱ����
	typedef shared_ptr<string> smart_ptr;

	smart_ptr films[2] = {
		smart_ptr(new string("Fowl Balls")),
		smart_ptr(new string("Duck Walks"))
	};
	smart_ptr pwin = films[1];
	cout << "Testing: " << typeid(pwin).name() << endl;
	for (auto ptr : films) { cout << *ptr << endl; }


	return 0;
}

/*
	Object created!
	using auto_ptr
	Object deleted!
	Object created!
	using shared_ptr
	Object deleted!
	Object created!
	using unique_ptr
	Object deleted!
	************************************************
	Testing: class std::shared_ptr<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >
	Fowl Balls
	Duck Walks
*/