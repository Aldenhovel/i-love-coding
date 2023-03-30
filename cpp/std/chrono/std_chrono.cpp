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
		// ʹ�� system_clock::now() ��ȡ��ǰʱ�䣬�Ǹ� time_point ����
		system_clock::time_point today = system_clock::now();

		// ����һ������Ϊһ�յ� duration
		day_type one_day(1);

		//  time_point + duration �õ���һ�� time_point
		system_clock::time_point tomorrow = today + one_day;

		// �� time_point ת��Ϊ time_t ������ C++ ��׼��ʱ��ṹ��
		std::time_t ttoday, ttomorrow;
		ttoday = system_clock::to_time_t(today);
		ttomorrow = system_clock::to_time_t(tomorrow);

		// ctime() �� time_t ת��Ϊ�ַ���
		cout << "Today is " << ctime(&ttoday) << endl;
		cout << "Tomorrow is " << ctime(&ttomorrow) << endl;

		// ʹ�� time_since_epoch() ���Լ���� 1970/1/1 �����ʱ����룬��һ�� duration ����λȡ���� time_point �ĵ�λ
		// �������ｫ time_point ת��Ϊ <days_type> ����
		typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
		time_point<system_clock, days_type> today2 = time_point_cast<days_type>(system_clock::now());	
		std::cout << today2.time_since_epoch().count() << " days since epoch" << std::endl;

	}

	void clock_demo() {
		using std::chrono::system_clock;

		// ʹ�� now() ��ȡ��ǰʱ�Ӳ���һ�� duration ����
		day_type one_day(1);
		system_clock::time_point today = system_clock::now();
		system_clock::time_point tomorrow = today + one_day;

		// ת��Ϊ std::time_t
		std::time_t ttoday = system_clock::to_time_t(today);
		std::time_t ttomorrow = system_clock::to_time_t(tomorrow);

		// ʹ�� ctime ��ʽ�������
		cout << ctime(&ttoday) << ctime(&ttomorrow) << endl;


		using namespace std::chrono;
		// ʹ�� steady_clock ͳ�ƴ�ӡ 1000 �Ǻ�����ʱ��
		steady_clock::time_point t1 = steady_clock::now();
		for (int i = 0; i < 1000; i++) cout << "*";
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		cout << "It took me " << time_span.count() << "seconds to print 1k stars.";


	}

}
