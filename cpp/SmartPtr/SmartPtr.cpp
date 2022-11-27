#include <iostream>
#include <string>

// 智能指针需要引入 <memery> ，处在 namespace std 中
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

	// 智能指针包含 auto_ptr<T> shared_ptr<T> unique_ptr<T> 只存在于本代码块
	// 过期后会被制动释放，无需手动 delete
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

	// auto_ptr shared_ptr unique_ptr 的使用区别
	// 由于智能指针会被自动释放，所以当多个指针指向同一地址时有可能会出现
	// 同一个地址被多次 delete 的情况，所以需要分 auto shared unique

	// 使用 auto_ptr 会出现运行时报错，因为 films[1] 已经将引用释放给了 pwin
	// 再使用 films[1] 时发现是空指针，报错
	// 使用 shared_ptr 可以正常运行，因为它会统计当所有指针都释放后才 delete 对象
	// 使用 unique_ptr 会在编译时报错
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