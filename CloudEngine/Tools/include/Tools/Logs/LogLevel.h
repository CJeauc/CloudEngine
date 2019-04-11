#pragma once

#include "string"

namespace Debug
{
	enum class LogLevel : uint8_t
	{
		INFO,
		DEBUG_,
		WARNING,
		ERROR_,
		FATAL
	};

	inline std::string logLevelToStr(const LogLevel p_log)
	{
		switch(p_log)
		{
		case LogLevel::INFO :
			return "INFO";

		case LogLevel::DEBUG_:
			return "DEBUG_";

		case LogLevel::WARNING:
			return "WARNING";

		case LogLevel::ERROR_:
			return "ERROR_";

		case LogLevel::FATAL:
			return "FATAL";

		default:
			return "";
		}
	}
}
