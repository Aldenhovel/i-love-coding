#include "Time.h"

using namespace Demos;
Time::Time() {
	hours = 0;
	minutes = 0;
}

Time::Time(int h, int m) {
	hours = h;
	minutes = m;
}

void Time::addHours(int h) {
	hours += h;
}

void Time::addMinutes(int m) {
	minutes += m;
}

void Time::reset(int h, int m) {
	hours = h;
	minutes = m;
}

Time Time::operator+(const Time &t) const {
	Time sum;
	int tot1, tot2;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

Time Time::operator-(const Time &t) const {
	Time diff;
	int tot1, tot2;
	tot1 = t.minutes + t.hours * 60;
	tot2 = minutes + hours * 60;
	diff.minutes = (tot2 - tot1) % 60;
	diff.hours = (tot2 - tot1) / 60;
	return diff;
}

Time Time::operator*(double n) const {
	Time res;
	long tot = n * (minutes + 60 * hours);
	res.minutes = tot / 60;
	res.hours = tot % 60;
	return res;
}

void Time::show() const {
	cout << hours << " hr(s), " << minutes << " min(s)" << endl;
}