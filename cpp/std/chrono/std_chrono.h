#pragma once
#include <chrono>


namespace myspace {
	void fn(int);

	typedef std::chrono::duration<int> seconds_type;
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60 * 24>> day_type;


	// time_point 的相关用法

	void time_point_demo();
	void clock_demo();
	


}
