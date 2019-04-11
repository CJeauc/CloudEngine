#pragma once
#include "LogSink.h"

namespace Debug
{
	class ConsoleLog : public LogSink
	{
	public:
		ConsoleLog() = default;
		~ConsoleLog() = default;
		void LogLine(const std::string& p_message, const char* p_function, const char* p_file, int p_line, LogLevel p_logLevel) override;
		void SimpleLog(const std::string& p_message, LogLevel p_logLevel) override;
	};
}
