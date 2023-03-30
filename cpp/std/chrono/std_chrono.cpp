#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <chrono>
#include <ctime>
#include "std_chrono.h"

using namespace std;
using std::chrono::system_clock;
using namespace std::chrono;

namespace myspace {
	
	typedef std::chrono::duration<int> seconds_type;
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;

	void time_point_demo() {
		// 使用 system_clock::now() 获取当前时间，是个 time_point 对象
		system_clock::time_point today = system_clock::now();

		// 定义一个长度为一日的 duration
		day_type one_day(1);

		//  time_point + duration 得到另一个 time_point
		system_clock::time_point tomorrow = today + one_day;

		// 将 time_point 转化为 time_t ，它是 C++ 标准的时间结构体
		std::time_t ttoday, ttomorrow;
		ttoday = system_clock::to_time_t(today);
		ttomorrow = system_clock::to_time_t(tomorrow);

		// ctime() 将 time_t 转化为字符串
		cout << "Today is " << ctime(&ttoday) << endl;
		cout << "Tomorrow is " << ctime(&ttomorrow) << endl;

		// 使用 time_since_epoch() 可以计算从 1970/1/1 至今的时间距离，是一个 duration ，单位取决于 time_point 的单位
		// 例如这里将 time_point 转化为 <days_type> 类型
		typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
		time_point<system_clock, days_type> today2 = time_point_cast<days_type>(system_clock::now());	
		std::cout << today2.time_since_epoch().count() << " days since epoch" << std::endl;

	}

	void clock_demo() {
		using std::chrono::system_clock;

		// 使用 now() 获取当前时钟并与一个 duration 计算
		day_type one_day(1);
		system_clock::time_point today = system_clock::now();
		system_clock::time_point tomorrow = today + one_day;

		// 转化为 std::time_t
		std::time_t ttoday = system_clock::to_time_t(today);
		std::time_t ttomorrow = system_clock::to_time_t(tomorrow);

		// 使用 ctime 格式化并输出
		cout << ctime(&ttoday) << ctime(&ttomorrow) << endl;


		using namespace std::chrono;
		// 使用 steady_clock 统计打印 1000 星号所需时间
		steady_clock::time_point t1 = steady_clock::now();
		for (int i = 0; i < 1000; i++) cout << "*";
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		cout << "It took me " << time_span.count() << "seconds to print 1k stars.";


	}

}
