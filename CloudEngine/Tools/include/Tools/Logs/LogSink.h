#pragma once
#include "LogLevel.h"

namespace Debug
{
	class LogSink
	{
	public:
		LogSink() = default;
		virtual ~LogSink() = default;

		virtual void LogLine(const std::string& p_message, const char* p_function, const char* p_file, int p_line, LogLevel p_logLevel) = 0;
		virtual void SimpleLog(const std::string& p_message, LogLevel p_logLevel) = 0;
	};
}