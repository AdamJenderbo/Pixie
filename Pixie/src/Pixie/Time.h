#pragma once
#include <string>

namespace Pixie
{
	class TimePoint
	{
	public:

		TimePoint(int hour, int minute, int second);

		std::string ToString();

	private:
		int hour;
		int minute;
		int second;
	};

	class Time
	{
	public:
		static TimePoint Now();
	};
}
