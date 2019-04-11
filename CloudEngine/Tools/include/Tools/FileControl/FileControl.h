#pragma once
#include "Tools/ToolsAPI.h"
#include "map"
#include "fstream"


//# if (_MSC_VER <= 1915)
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
//#else
//	#include <filesystem>
//	namespace fs = std::filesystem;
//#endif

namespace Utils
{	
	class  TOOLS_API FileControl
	{
	public :
		FileControl() = default;
		FileControl(const FileControl& p_other) = default;
		~FileControl();

		void CreateDirectory(const std::string& p_directory);
		
		void CreateMyFile(const std::string& p_path);
		void CreateAndOpenFile(const std::string& p_path);
		bool OpenFile(const std::string& p_path);

		void SetCursorWrite(const uint16_t& p_offsetFromBeg);
		void CloseFile();

		void EmptyDirectory(const std::string& p_pathDirectory, const std::string& p_fileToDestroy, int p_numberOfFileToRemain) const;

		fs::path GetDirectory(const std::string& p_directory) const;
		fs::path GetFile() const;

		std::string GetDirectoryPath(const std::string& p_directory) const;
		std::string ConcatenatePath(const std::string& p_fileName,const std::string& p_directoryPath);
		
		template<typename T>
		void WriteData(const std::string& p_file, T* p_dataToWrite, const uint8_t p_size = 1)
		{
			if (m_file.is_open())
			{
				m_file.write(static_cast<const char*>(p_dataToWrite), sizeof(T) * p_size);
				m_file.close();
			}
			else
			{
				OpenFile(p_file);
				WriteData(p_file, p_dataToWrite, p_size);
			}				
		}

		template<typename T>
		void WriteData(const std::string& p_file, T p_dataToWrite, const uint8_t p_size = 1)
		{
			if (m_file.is_open())
			{
				m_file.write(static_cast<const char*>(p_dataToWrite), sizeof(T) * p_size);
				m_file.close();
			}
			else			
			{
				OpenFile(p_file);
				WriteData(p_file, p_dataToWrite, p_size);
			}
		}
		
	private:
		std::ofstream m_file;
		fs::path m_pathFile;
		std::map<fs::path, std::string> m_directories;
		;
	};
}
