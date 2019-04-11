#pragma once

#include "Core/stdafx.h"

namespace Core
{
	enum class SystemPriority : uint16_t
	{
		LOWEST_SYSTEM_PRIORITY = std::numeric_limits<uint16_t>::min(),

		VERY_LOW_SYSTEM_PRIORITY = 99,
		LOW_SYSTEM_PRIORITY = 100,

		NORMAL_SYSTEM_PRIORITY = 200,

		MEDIUM_SYSTEM_PRIORITY = 300,

		HIGH_SYSTEM_PRIORITY = 400,
		VERY_HIGH_SYSTEM_PRIORITY = 401,

		HIGHEST_SYSTEM_PRIORITY = std::numeric_limits<uint16_t>::max()
	};

	inline SystemPriority operator - (const SystemPriority& p_first, const SystemPriority& p_second)
	{
		return static_cast<SystemPriority>(static_cast<uint16_t>(p_first) - static_cast<uint16_t>(p_second));
	}
}