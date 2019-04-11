#pragma once

#include "Tools/stdafx.h"
#include "Tools/ToolsAPI.h"

namespace Tools
{
	namespace Memory
	{
		union TOOLS_API Ptr
		{
			uintptr_t asSize;
			void* asPtr;
		};

		class TOOLS_API Allocator
		{
		public:
			Allocator(const size_t p_totalSize);
			virtual ~Allocator();

			virtual void* Allocate(const size_t p_size, const uint8_t p_alignment = 0) = 0;
			virtual void Free(void* ptr) = 0;

			virtual void Init() = 0;

		protected:
			size_t m_totalSize;

			Ptr m_startPtr;
			size_t m_offset;

			size_t m_peak;
		};
	}
}
