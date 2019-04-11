#pragma once
#include "Tools/ToolsAPI.h"

#include "LogLevel.h"
#include "ConsoleLog.h"
#include "FileLogger.h"
#include "Tools/Event/Event.h"

#define LOG(Logger_, Message_, ...)						\
	Debug::Log::Logger_(								\
		static_cast<std::ostringstream&>(				\
			std::ostringstream().flush() << Message_	\
			).str(),									\
		__FUNCTION__,									\
		__FILE__,										\
		__LINE__, 										\
		__VA_ARGS__										\
	);

#define SLOG(Logger_, Message_, ...) \
	Debug::Log::Logger_(									\
			static_cast<std::ostringstream&>(				\
			std::ostringstream().flush() << Message_		\
			).str(), 										\
			__VA_ARGS__										\
	);

namespace Debug
{
	enum class LogStream : uint8_t
	{
		CONSOLE	 = (1 << 0),
		FILE	 = (1 << 1),
		QT		 = (1 << 2)
	};


	class TOOLS_API Log
	{
	public :
		explicit Log(const LogLevel p_level);

		void operator()(const std::string& p_message, const char* p_function, const char* p_file, const int p_line, LogStream p_flags = Log::StreamToUse()) const;
		void operator()(const std::string& p_message, LogStream p_flags = Log::StreamToUse()) const;

		static Log& Info();
		static Log& Debug();
		static Log& Warning();
		static Log& Error();
		static Log& Fatal();

	public:
		static Tools::Event<const std::string&, const char*, const char*, int, LogLevel> m_event;
		static bool s_useEvents;

	private:
		static LogStream StreamToUse() { return Log::s_useEvents ? LogStream::QT : LogStream::CONSOLE; }

		static class ConsoleLog s_consoleLog;
		static class FileLogger s_fileLog;
		
		LogLevel m_level;

	};

	inline LogStream operator|(LogStream lhs, LogStream rhs)
	{
		return static_cast<LogStream>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	}

	inline LogStream operator&(LogStream lhs, LogStream rhs)
	{
		return static_cast<LogStream>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	}

	inline bool operator!=(LogStream lhs, const uint8_t rhs)
	{
		return static_cast<uint8_t>(lhs) != rhs;
	}
	// TODO : Add maybe a mutex
}