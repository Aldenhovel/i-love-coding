#pragma once
#include <string>
#include <iostream>

using namespace std;

class Worker {
private:
	string fullname;
	long id;
protected:

	// Set �� Show ��ʹ�õ������������Ϣ������ Show ��������� fullname id ��
	// ���ﶨ�� Data, Get �Ƿ���̳У�ֻ������޸������Լ������Ϣ
	// ����ڶ��ؼ̳��п��Է���ص���ÿ�����Լ��� Data() �� Get()
	// ��Ϊ���麯������Ҫ�ڼ̳е����в���
	virtual void Data() const;
	virtual void Get();
public:
	Worker() : fullname("no one"), id(0L) {};
	Worker(const string &s, long n) : fullname(s), id(n) {};

	// = 0 �������麯����
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
	// enum ö�����ͣ��ȼ��� #define other 0, #define alto 1 ......
	// Ҳ����ָ��ֵ������һ��ö������ֵΪǰһ���ļ� 1 
	enum {other, alto, contralto, soprano, bass, baritone, tenor};
	enum {Vtype = 7};
	void Data() const;
	void Get();
private:
	// ���ﶨ����һ������Ϊ 7 �� char* ���飬�� 7 ���ַ�������ʾ���� 7 �� voice
	// ��Ҫʹ�� char* Singer::pv[] = { ... } ��ʼ��
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

	// �����������캯�������ɻ��๹�������࣬��Ҫ��ʾ��ָ������Ĺ��캯��
	SingingWaiter(const Worker &wk, int p = 0, int v = other) 
		: Worker(wk), Waiter(wk, p), Singer(wk, v) {};

	// ������캯������ Waiter �� v ���������� SingingWaiter
	// ��������Ҫ��ʽ�ص��� Worker(wt) ����ʼ�� Worker ����
	SingingWaiter(const Waiter &wt, int v = other)
		: Worker(wt), Waiter(wt), Singer(wt, v) {};
	SingingWaiter(const Singer &sg, int p = 0)
		: Worker(sg), Waiter(sg, p), Singer(sg) {};
	void Set();
	void Show() const;
};