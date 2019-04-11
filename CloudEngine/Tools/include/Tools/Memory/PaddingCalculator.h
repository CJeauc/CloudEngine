#pragma once

#include "Tools/Memory/Allocator.h"

namespace Tools
{
	namespace Memory
	{
		TOOLS_API size_t CalculatePadding(Ptr p_currentAddress, size_t p_alignment);
		TOOLS_API size_t CalculatePadding(const Ptr p_currentAddress,
		                               const size_t p_alignment,
		                               const size_t p_headerSize);
	}
}
