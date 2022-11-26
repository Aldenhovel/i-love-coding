#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Grand {
private:
	int hold;
public:
	Grand(int h = 0) : hold(h) {};
	virtual void Speak() const { cout << "I M Grand" << endl; }
	virtual int Value() const { return hold; }
};

class Superb : public Grand {
public:
	Superb(int h = 0) : Grand(h) {};
	void Speak() const { cout << "I M Superb" << endl; }
	virtual void Say() const { cout << "I hold superb value of " << Value() << endl; }
};

class Magnificent : public Superb {
private:
	char ch;
public:
	Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) {};
	void Speak() const { cout << "I M Magnificent" << endl; }
	void Say() const { cout << "I hold the char " << ch << " and value " << Value() << endl; }
};

Grand* GetOne() {
	// 随机生成 Grand Superb Magnificent 三个类中的一个
	Grand *p = 0;
	switch(std::rand() % 3) {
		case 0:
			p = new Grand(std::rand() % 100);
			break;
		case 1:
			p = new Superb(std::rand() % 100);
			break;
		case 2:
			p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
	}
	return p;
}

int main() {
	std::srand(std::time(0));
	Grand *pg;
	Superb *ps;
	for (int i = 0; i < 5; i++) {
		cout << "*******************" << endl;
		pg = GetOne();
		pg->Speak();

		// 这里尝试使用 dynamic_cast<Type>() 转换指针
		// 结果是只有 Superb 和 Magnificent 的 pg 可以运行下面代码
		// 这是因为继承关系是 Grand->Superb->Magnificent ，只能是将 Superb 或者 Magnificent
		// 转换为 Superb ，当遇到 Grand* 转 Superb* 或 Magnificent* 时是不安全的， dynamic_cast 会作出限制
		if  (ps = dynamic_cast<Superb*>(pg)) ps->Say();
	}
	return 0;
}

/*
*******************
I M Magnificent
I hold the char R and value 36
*******************
I M Superb
I hold superb value of 12
*******************
I M Superb
I hold superb value of 66
*******************
I M Grand
*******************
I M Grand
*/