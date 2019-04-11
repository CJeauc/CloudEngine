#pragma once

#include "Allocator.h"

namespace Tools
{
	namespace Memory
	{
		class TOOLS_API LinearAllocator : Allocator
		{
		public:
			LinearAllocator(const size_t p_totalSize);
			~LinearAllocator() override;

			virtual void Init() override;
			virtual void Reset();
			virtual void* Allocate(const size_t p_size, const uint8_t p_alignment = 0) override;
			virtual void Free(void* p_ptr) override;
		};
	}
}