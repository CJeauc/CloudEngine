#include "Tools/stdafx.h"
#include "Tools/Memory/LinearAllocator.h"
#include "Tools/Memory/PaddingCalculator.h"
#include "Tools/Logs/Log.h"

using namespace Tools::Memory;

LinearAllocator::LinearAllocator(const size_t p_totalSize)
	: Allocator(p_totalSize) {}

LinearAllocator::~LinearAllocator()
{
	free(m_startPtr.asPtr);
	m_startPtr.asPtr = nullptr;
}

void LinearAllocator::Init()
{
	if (m_startPtr.asPtr)
		free(m_startPtr.asPtr);

	m_startPtr.asPtr = malloc(m_totalSize);
	m_offset = 0;
}

void LinearAllocator::Reset()
{
	m_offset = 0;
}

void* LinearAllocator::Allocate(const size_t p_size, const uint8_t p_alignment)
{
	const Ptr currentAddress = { m_startPtr.asSize + m_offset };
	// Find the padding to next aligned memory address 
	const std::size_t padding = CalculatePadding(currentAddress, p_alignment);

	// Test if there is still place for an other allocation
	if (m_offset + padding + p_size > m_totalSize)
		return nullptr;

	m_offset += padding + p_size;

	// Calculate the memory utilization
	m_peak = std::max(m_peak, m_offset);

	const Ptr nextAddress = { currentAddress.asSize + padding };

	return nextAddress.asPtr;
}

void LinearAllocator::Free(void* p_ptr)
{
	LOG(Log::Warning(), "LinearAllocator doesn't provide Free() method, Use Reset() method instead");
}
