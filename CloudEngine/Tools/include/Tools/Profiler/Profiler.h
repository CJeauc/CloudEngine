#pragma once
#include "Tools/Timer/Stopwatch.h"
namespace Debug
{
	class Profiler
	{
	public:
		struct Data_
		{
			unsigned int count;
			__int64 timeElapsed;

			void Destroy()
			{
				Profiler::Save(*this);
			}
		};

		Profiler();
		Profiler(const Profiler& p_other) noexcept;
		~Profiler();

		void StartRunning();
		void StopRunning();

		static void Save(Data_& p_data);
	private:
		Utils::preciseStopwatch m_stopWatch;

		static __int64 __ELAPSED_TIME;
	};
}
