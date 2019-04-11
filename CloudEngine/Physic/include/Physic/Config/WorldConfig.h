#pragma once

#define EARTH_GRAVITY CloudMath::Vector3f{0, -9.80665f, 0}
#include "CloudMath.h"

namespace Physic
{
	struct WorldConfig
	{
		CloudMath::Vector3f gravity;
	};
}
