#include "Tools/stdafx.h"

#include "Tools/Logs/Log.h"
#include "Tools/Logs/ConsoleLog.h"
#include "Tools/Logs/FileLogger.h"

using namespace Debug;

ConsoleLog Log::s_consoleLog = ConsoleLog();

FileLogger Log::s_fileLog = FileLogger();

Tools::Event<const std::string&, const char*, const char*, int, LogLevel> Log::m_event ;

bool Log::s_useEvents = false;

Log::Log(const LogLevel p_level) : m_level(p_level)
{}

void Log::operator()(const std::string& p_message, const char* p_function, const char* p_file, const int p_line,
	LogStream p_flags) const
{
	if (p_flags != 0)
	{
		if ((p_flags & LogStream::CONSOLE) != 0)
			s_consoleLog.LogLine(p_message, p_function, p_file, p_line, m_level);
		if ((p_flags & LogStream::FILE) != 0)
			s_fileLog.LogLine(p_message, p_function, p_file, p_line, m_level);
		if ((p_flags & LogStream::QT) != 0)
			m_event.Invoke(p_message, p_function, p_file, p_line, m_level);
	}
}

void Log::operator()(const std::string& p_message, LogStream p_flags) const
{
	if (p_flags != 0)
	{
		if ((p_flags & LogStream::CONSOLE) != 0)
			s_consoleLog.SimpleLog(p_message, m_level);
		if ((p_flags & LogStream::FILE) != 0)
			s_fileLog.SimpleLog(p_message, m_level);
		if ((p_flags & LogStream::QT) != 0)
			m_event.Invoke(p_message, nullptr, nullptr,-1, m_level);
	}
}

Log& Log::Info()
{
	static Log logger(LogLevel::INFO);
	return logger;
}

Log& Log::Debug()
{
	static Log logger(LogLevel::DEBUG_);
	return logger;
}

Log& Log::Warning()
{
	static Log logger(LogLevel::WARNING);
	return logger;
}

Log& Log::Error()
{
	static Log logger(LogLevel::ERROR_);
	return logger;
}

Log& Log::Fatal()
{
	static Log logger(LogLevel::FATAL);
	return logger;
}
