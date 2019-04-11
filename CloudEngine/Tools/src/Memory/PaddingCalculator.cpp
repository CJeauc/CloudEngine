#include "Tools/stdafx.h"
#include "Tools/Memory/PaddingCalculator.h"

size_t Tools::Memory::CalculatePadding(Ptr p_currentAddress, size_t p_alignment)
{
	if (p_alignment == 0)
		return 0;

	const size_t padding = p_alignment - (p_currentAddress.asSize % p_alignment);
	return padding == p_alignment ? 0 : padding;
}

size_t Tools::Memory::CalculatePadding(const Ptr p_currentAddress,
                                       const size_t p_alignment,
                                       const size_t p_headerSize)
{
	size_t padding = CalculatePadding(p_currentAddress, p_alignment);
	size_t neededSpace = p_headerSize;

	if (padding < p_headerSize)
	{
		neededSpace -= padding;
		padding += p_alignment * (neededSpace / p_alignment);

		if (neededSpace % p_alignment > 0)
			padding += p_alignment;
	}

	return padding;
}
