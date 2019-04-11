#pragma once

#include "LogSink.h"

#include "Tools/FileControl/FileControl.h"


namespace Debug
{
	class FileLogger : public LogSink
	{
	public:
		FileLogger();
		FileLogger(const FileLogger& p_other) noexcept;
		~FileLogger();

		void LogLine(const std::string& p_message, const char* p_function, const char* p_file, int p_line, LogLevel p_logLevel) override;
		void SimpleLog(const std::string& p_message, LogLevel p_logLevel) override;
	private:
		class Utils::FileControl m_controlFile;
	};
}
