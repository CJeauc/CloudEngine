#pragma once

#include "Profiler.h"
#include "Tools/FileControl/FileControl.h"

namespace Debug
{
	enum class ProfilerStream: uint8_t
	{
		FILE = (0 << 0)
	};

	class ProfilerLoader
	{
	public:

		ProfilerLoader();
		ProfilerLoader(const ProfilerLoader& p_other) noexcept;
		~ProfilerLoader();

		void Load(ProfilerStream p_stream = ProfilerStream::FILE);
	private:
		class Utils::FileControl m_controlFile;
	};
}