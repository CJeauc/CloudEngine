#include "Tools/stdafx.h"
#include "Tools/Logs/FileLogger.h"
#include "Tools/Assert/Assertion.h"

using namespace Debug;
using namespace Utils;

FileLogger::FileLogger()
{
	m_controlFile.CreateDirectory("Logs");
	m_controlFile.CreateAndOpenFile(m_controlFile.ConcatenatePath("Logs.txt", m_controlFile.GetDirectoryPath("Logs")));
}

FileLogger::FileLogger(const FileLogger& p_other) noexcept
{}

FileLogger::~FileLogger()
{
	m_controlFile.CloseFile();
	m_controlFile.EmptyDirectory(m_controlFile.GetDirectoryPath("Logs"), "_Logs.txt" , 5);
}

void FileLogger::LogLine(const std::string& p_message, const char* p_function, const char* p_file, int p_line,
	LogLevel p_logLevel)
{
	std::string file = p_file;
	file = file.substr(file.find_last_of("\\") + 1);

	std::string temp("\n::  " + logLevelToStr(p_logLevel) + "   :: "
		+ p_function + "() in " + file + "("
		+ std::to_string(p_line) + ")\n" + "::  MESSAGE ::" + p_message.c_str());
	m_controlFile.WriteData(m_controlFile.GetFile().string(), temp.c_str(), static_cast<uint8_t>(temp.size()));
}

void FileLogger::SimpleLog(const std::string& p_message, LogLevel p_logLevel)
{
	m_controlFile.WriteData(m_controlFile.GetFile().string(), p_message.c_str(), static_cast<uint8_t>(p_message.size()));
}
