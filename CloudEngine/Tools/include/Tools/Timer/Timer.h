#pragma once
#include "Tools/ToolsAPI.h"

namespace Utils
{
	class TOOLS_API Timer
	{
	private:
		Timer() = delete;
		~Timer() = delete;

	public:
		using clock = std::chrono::high_resolution_clock;
		using ms	= std::chrono::duration< double, std::milli>;
		using sec	= std::chrono::duration<double>;

		using frameTime = sec;

		static std::string TimeStampPerso();

	};
}
