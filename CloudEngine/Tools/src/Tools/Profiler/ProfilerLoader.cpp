#include "Tools/stdafx.h"

#include "Tools/Profiler/ProfilerLoader.h"

using namespace Debug;

ProfilerLoader::ProfilerLoader()
{
	m_controlFile.CreateDirectoryA("Profiler");
	m_controlFile.ConcatenatePath("Profiler.txt", m_controlFile.GetDirectoryPath("Profiler"));
}

ProfilerLoader::ProfilerLoader(const ProfilerLoader& p_other) noexcept
{}

ProfilerLoader::~ProfilerLoader()
{
	m_controlFile.CloseFile();
	m_controlFile.EmptyDirectory(m_controlFile.GetDirectoryPath("Profiler"), "_Profiler.txt", 10);
}

void ProfilerLoader::Load(ProfilerStream p_stream)
{
	if(p_stream == ProfilerStream::FILE)
	{
		/// call function to display in file.
		/// Load from Profiler struct of information. 
	}
}
