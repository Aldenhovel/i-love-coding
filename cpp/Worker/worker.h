#pragma once
#include <string>
#include <iostream>

using namespace std;

class Worker {
private:
	string fullname;
	long id;
protected:

	// Set 和 Show 会使用到本类的所有信息，比如 Show 会完整输出 fullname id 等
	// 这里定义 Data, Get 是方便继承，只输出或修改属于自己类的信息
	// 因此在多重继承中可以方便地调用每个类自己的 Data() 和 Get()
	// 因为是虚函数，需要在继承的类中补充
	virtual void Data() const;
	virtual void Get();
public:
	Worker() : fullname("no one"), id(0L) {};
	Worker(const string &s, long n) : fullname(s), id(n) {};

	// = 0 将构造虚函数表
	virtual ~Worker() = 0;
	virtual void Set();
	virtual void Show() const;
};


class Waiter : virtual public Worker {
private:
	int panache;
protected:
	void Data() const;
	void Get();
public:
	Waiter() : Worker(), panache(0) {};
	Waiter(const string &s, long n, int p = 0) : Worker(s, n), panache(p) {};
	Waiter(const Worker &wk, int p = 0) : Worker(wk), panache(p) {};
	void Set();
	void Show() const;
};


class Singer : virtual public Worker {
protected:
	// enum 枚举类型，等价于 #define other 0, #define alto 1 ......
	// 也可以指定值，后面一个枚举类型值为前一个的加 1 
	enum {other, alto, contralto, soprano, bass, baritone, tenor};
	enum {Vtype = 7};
	void Data() const;
	void Get();
private:
	// 这里定义了一个长度为 7 的 char* 数组，即 7 个字符串，表示上面 7 种 voice
	// 需要使用 char* Singer::pv[] = { ... } 初始化
	static char *pv[Vtype];
	int voice;
public:
	Singer() :Worker(), voice(other) {};
	Singer(const string &s, long n, int v = other) : Worker(s, n), voice(v) {};
	Singer(const Worker &wk, int v = other) :Worker(wk), voice(v) {};
	void Set();
	void Show() const;
};

class SingingWaiter : public Singer, public Waiter {
protected:
	void Data() const;
	void Get();
public:
	SingingWaiter() {};
	SingingWaiter(const string &s, long n, int p = 0, int v = other)
		: Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {};

	// 以下三个构造函数都是由基类构造派生类，需要显示地指出基类的构造函数
	SingingWaiter(const Worker &wk, int p = 0, int v = other) 
		: Worker(wk), Waiter(wk, p), Singer(wk, v) {};

	// 这个构造函数接收 Waiter 和 v 参数来构造 SingingWaiter
	// 但还是需要显式地调用 Worker(wt) 来初始化 Worker 基类
	SingingWaiter(const Waiter &wt, int v = other)
		: Worker(wt), Waiter(wt), Singer(wt, v) {};
	SingingWaiter(const Singer &sg, int p = 0)
		: Worker(sg), Waiter(sg, p), Singer(sg) {};
	void Set();
	void Show() const;
};