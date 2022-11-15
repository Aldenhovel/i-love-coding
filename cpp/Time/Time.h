#pragma once
#include <iostream>

using namespace std;
namespace Demos {
	class Time {
	private:
		int hours;
		int minutes;
	public:
		Time();
		Time(int h, int m=0);

		void addHours(int h);

		void addMinutes(int m);

		void reset(int h = 0, int m = 0);

		// 重载 self + t
		Time operator+(const Time &t) const;

		// 重载 self - t
		Time operator-(const Time &t) const;

		// 重载 self * n
		Time operator*(double n) const;

		// 重载 n * self 需要使用友元，让 double 类型可以访问 Time 的私有成员
		// 注意这个函数应该处于 namespace Demos 中，需要使用 Demos::operator* 来定义
		friend Time operator*(double n, const Time &t);

		//重载 << 让它支持 cout 输出
		friend ostream& operator<<(ostream& os, const Time &t);

		void show() const;
	};
}
