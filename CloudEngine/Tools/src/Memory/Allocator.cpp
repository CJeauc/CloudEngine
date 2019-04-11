#include "Tools/stdafx.h"
#include "Tools/Memory/Allocator.h"


using namespace Tools::Memory;

Allocator::Allocator(const size_t p_totalSize)
	: m_totalSize(p_totalSize), m_startPtr{}, m_offset(0), m_peak(0) { }

Allocator::~Allocator()
{
	m_totalSize = 0;
}
