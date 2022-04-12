#include "pxpch.h"
#include "Time.h"
#include <chrono>
#include <ctime>

Pixie::TimePoint::TimePoint(int hour, int minute, int second)
	: hour(hour), minute(minute), second(second)
{
}

std::string Pixie::TimePoint::ToString()
{
	return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}

Pixie::TimePoint Pixie::Time::Now()
{
	auto now = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(now);
	std::tm nowLocal{};
	localtime_s(&nowLocal, &tt);
	TimePoint timePoint(nowLocal.tm_hour, nowLocal.tm_min, nowLocal.tm_sec);
	return timePoint;
}

