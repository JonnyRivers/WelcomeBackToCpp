#include "stdafx.h"
#include "DateTime.h"

#include <chrono>
#include <ctime>
#include <iostream>

DateTime::DateTime()
{
}


DateTime::~DateTime()
{
}

std::ostream& operator <<(std::ostream& os, const std::chrono::system_clock::time_point& tp)
{
	std::time_t tt = std::chrono::system_clock::to_time_t(tp);
	char buffer[256];
	ctime_s(buffer, sizeof(buffer), &tt);

	os << buffer;

	return os;
}

void DateTime::Run()
{
	// DateTime now = DateTime.Now;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// TimeSpan oneDay = TimeSpan.FromDays(1);
	// DateTime tomorrow = now + oneDay;
	std::chrono::duration<int, std::ratio<60 * 60 * 24>> one_day(1);
	std::chrono::system_clock::time_point tomorrow = now + one_day;

	// Console.WriteLine(now);
	std::time_t tt = std::chrono::system_clock::to_time_t(now);
	std::cout << "today is: " << now << std::endl;
}