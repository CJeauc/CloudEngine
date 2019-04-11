#pragma once

#include "Allocator.h"

namespace Tools
{
	namespace Memory
	{
		class TOOLS_API PoolAllocator : public Allocator
		{
		public:
			PoolAllocator(size_t p_totalSize, size_t p_chunkSize);
			~PoolAllocator();

			void Init() override;
			void Reset();

			void* Allocate(const size_t p_size, const uint8_t p_alignment) override;
			void Free(void* p_ptr) override;

		private:
			const size_t	m_chunkSize;
			Ptr*			m_freeList;
		};
	}
}