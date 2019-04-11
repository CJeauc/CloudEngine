#pragma once

#include "Tools/ToolsAPI.h"

#include <chrono>
#include <atomic>

namespace Utils
{
	template<typename Clock = std::chrono::high_resolution_clock>
	class Stopwatch
	{
	public:
		Stopwatch() : m_startPoint(Clock::now()) {}

		void Start() { m_activatedPoint = Clock::now(); }

		template<typename Rep = typename Clock::duration::rep, typename Units = typename Clock::duration>
		Rep ElapsedTime() const
		{
			std::atomic_thread_fence(std::memory_order_relaxed);
			auto countedTime = std::chrono::duration_cast<Units>(Clock::now() - m_startPoint).count();
			std::atomic_thread_fence(std::memory_order_relaxed);
			return static_cast<Rep>(countedTime);
		}

		template<typename Rep = typename Clock::duration::rep, typename Units = typename Clock::duration>
		Rep ElapsedTimeActivated() const
		{
			std::atomic_thread_fence(std::memory_order_relaxed);
			auto countedTime = std::chrono::duration_cast<Units>(Clock::now() - m_activatedPoint).count();
			std::atomic_thread_fence(std::memory_order_relaxed);
			return static_cast<Rep>(countedTime);
		}
	private:

		const typename Clock::time_point m_startPoint;
		typename std::chrono::time_point<Clock> m_activatedPoint;
	};

	using preciseStopwatch = Stopwatch<>;
	using systemStopwatch = Stopwatch<std::chrono::system_clock>;
	using monotonicStopwatch = Stopwatch<std::chrono::steady_clock>;
}