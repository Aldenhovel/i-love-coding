#pragma once
#include <iostream>
#include <string>

using namespace std;
namespace Demos {
	
	// 基类
	class TennisPlayer {
	private:
		// 静态变量
		static string intro;

		// 一般变量
		string firstName;
		string lastName;
		bool hasTable;
	public:

		// 构造函数
		TennisPlayer(const string fn = "none", const string ln = "none", bool ht = false);
		
		// 普通函数
		string Name() const;
		bool HasTable() const;
		void ResetTable(bool ht);

		// 虚函数
		virtual ~TennisPlayer();
		virtual void Grettings();

		// 静态函数
		static void Intro();

		// 友元，重载输出
		friend ostream& operator<<(ostream& os, TennisPlayer &tp);
	};

	// public 继承 TennisPalyer 的 RatedPlater 类
	class RatedPlayer : public TennisPlayer {
	private:
		int rating;
	public:
		// 构造函数，复制构造函数
		RatedPlayer(const string fn = "none", const string ln = "none", bool ht = false, int r = 0);
		RatedPlayer(TennisPlayer &tp, int r);
		
		// 普通函数
		int Rating() const;
		void resetRating(int r);

		// 虚函数
		// 虚函数可以实现有区别的重载，如果不加虚函数，会调用指针或引用的函数
		// 如果使用虚函数可以始终调用指向的类本体的方法，如：
		// A a = A()
		// B:A *b = &a
		// b->fn is B::fn if fn is not virtual, because b is a B point
		// b->fn is A::fn if fn is virtual, because b point to class A
		virtual ~RatedPlayer();
		virtual void Greetings();

		// 友元
		friend ostream& operator<<(ostream& os, RatedPlayer &tp);

	};
}