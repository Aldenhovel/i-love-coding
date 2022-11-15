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

		// ���� self + t
		Time operator+(const Time &t) const;

		// ���� self - t
		Time operator-(const Time &t) const;

		// ���� self * n
		Time operator*(double n) const;

		// ���� n * self ��Ҫʹ����Ԫ���� double ���Ϳ��Է��� Time ��˽�г�Ա
		// ע���������Ӧ�ô��� namespace Demos �У���Ҫʹ�� Demos::operator* ������
		friend Time operator*(double n, const Time &t);

		//���� << ����֧�� cout ���
		friend ostream& operator<<(ostream& os, const Time &t);

		void show() const;
	};
}
