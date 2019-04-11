#include "Tools/stdafx.h"

#include "Tools/FileControl/FileControl.h"
#include "Tools/Assert/Assertion.h"
#include "Tools/Timer/Timer.h"

// disable warning unrecognized character
#pragma warning(push)
#pragma warning(disable: 4129)

using namespace Utils;

FileControl::~FileControl()
{
	CloseFile();
}

void FileControl::CreateMyFile(const std::string& p_path)
{
	std::ofstream file(p_path);	
	file.close();
}

void FileControl::CreateAndOpenFile(const std::string& p_path)
{
	CreateMyFile(p_path);
	OpenFile(p_path);
}



void FileControl::CreateDirectory(const std::string& p_directory)
{
	fs::path directory = p_directory;
	if (!fs::exists(directory))
	{
		SLOG(Log::Info(), "adding a directory : " << p_directory);
		fs::create_directory(directory);
	}	
	m_directories[directory] = p_directory;
}

void FileControl::SetCursorWrite(const uint16_t& p_offsetFromBeg)
{
	m_file.seekp(p_offsetFromBeg);
}

bool FileControl::OpenFile(const std::string& p_path)
{
	CloseFile();
	m_file.open(p_path, std::ios::in | std::ios::out | std::ios::app);
	if(!m_file.is_open())
	{
		std::cerr << "The file couldn't be opened." << '\n';
		return false;
	}
	return true;
}


fs::path  FileControl::GetDirectory(const std::string& p_directory) const
{
	for(auto it = m_directories.begin(); it != m_directories.end(); ++it)
	{
		if (it->second == p_directory)
			return it->first;
	}
	return {};
}

fs::path FileControl::GetFile() const
{
	return m_pathFile;
}

std::string FileControl::GetDirectoryPath(const std::string& p_directory) const
{
	std::string dirPath = GetDirectory(p_directory).filename().string();
	return dirPath;
}

std::string FileControl::ConcatenatePath(const std::string& p_fileName, const std::string& p_directoryPath)
{
	m_pathFile = p_directoryPath + "\/" + Timer::TimeStampPerso() + "_" + p_fileName;
	return m_pathFile.string();  
}


void FileControl::CloseFile()
{
	if(m_file.is_open())
		m_file.close();
}

void FileControl::EmptyDirectory(const std::string& p_pathDirectory, const std::string& p_fileToDestroy, int p_numberOfFileToRemain) const
{
	fs::path directory = p_pathDirectory;
	ASSERTD(fs::exists(directory), "Directory does not exist.");
	std::vector<fs::path> files;
	
	for(auto file : fs::directory_iterator(p_pathDirectory))
	{
		if(file.path().string().find(p_fileToDestroy) != std::string::npos)
			files.push_back(fs::path(file.path()));
	}

 	if(files.size() > p_numberOfFileToRemain)
	{
		for(auto i = 0; i < files.size() - p_numberOfFileToRemain; ++i)
		{
			fs::remove(files[i]);
		}
	}
}


#pragma warning(pop)
