#pragma once

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
		Time operator+ (const Time &t) const;
		Time operator- (const Time &t) const;
		Time operator* (double n) const;
		void show() const;
	};
}
