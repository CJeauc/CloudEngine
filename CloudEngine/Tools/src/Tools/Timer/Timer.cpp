#include "Tools/stdafx.h"

#include "Tools/Timer/Timer.h"

using namespace Utils;


std::string Timer::TimeStampPerso()
{
	const std::chrono::time_point<std::chrono::system_clock> temp = std::chrono::system_clock::now();
	std::time_t now = std::chrono::system_clock::to_time_t(temp);

	struct tm structTemp;
	char cstr[32]{};

	localtime_s(&structTemp, &now);
	return std::strftime(cstr, 32, "%m_%d_%H-%M", &structTemp) ? cstr : "";
}


