#include "Tools/stdafx.h"
#include "Tools/Memory/PoolAllocator.h"
#include "Tools/Assert/Assertion.h"
#include "Tools/Logs/Log.h"

using namespace Tools::Memory;

PoolAllocator::PoolAllocator(size_t p_totalSize, size_t p_chunkSize)
	: Allocator(p_totalSize), m_chunkSize(p_chunkSize), m_freeList(nullptr)
{
	ASSERTD(p_chunkSize >= 8, "Chunk size must be greater or equal to 8");
	ASSERTD(p_totalSize % p_chunkSize == 0, "Total Size must be a multiple of Chunk Size");
}

PoolAllocator::~PoolAllocator()
{
	if (m_startPtr.asPtr)
		free(m_startPtr.asPtr);
}

void PoolAllocator::Init()
{
	if (m_startPtr.asPtr == nullptr)
		m_startPtr.asPtr = malloc(m_totalSize);

	this->Reset();
}

void PoolAllocator::Reset()
{
	m_peak = 0;

	m_freeList = static_cast<Ptr*>(m_startPtr.asPtr);

	Ptr* pointer = m_freeList;
	const size_t numberChunks = static_cast<size_t>(m_totalSize / m_chunkSize);

	for (size_t i = 0; i < (numberChunks - 1); ++i)
	{
		pointer->asSize = (reinterpret_cast<uintptr_t>(pointer) + m_chunkSize);
		pointer = static_cast<Ptr*>(pointer->asPtr);
	}

	pointer->asPtr = nullptr;
}

void* PoolAllocator::Allocate(const size_t p_size, const uint8_t p_alignment)
{
	ASSERTD(p_size == m_chunkSize, "Allocation size must be equal to chunk size : " + std::to_string(m_chunkSize));

	if (!m_freeList)
	{
		//SLOG(Debug::Log::Warning(), m_startPtr.asPtr ? "The pool allocator is full" : "The pool allocator isn't initialized", Debug::LogStream::CONSOLE | Debug::LogStream::FILE);
		return nullptr;
	}


	void* pointer = m_freeList;

	m_freeList = static_cast<Ptr*>(m_freeList->asPtr);

	m_offset += m_chunkSize;
	m_peak = std::max(m_peak, m_offset);

	return pointer;
}

void PoolAllocator::Free(void* p_ptr)
{
	*(static_cast<void**>(p_ptr)) = m_freeList;

	m_freeList = static_cast<Ptr*>(p_ptr);

	m_offset -= m_chunkSize;
}
