#pragma once

#include "Core/stdafx.h"

namespace Core
{
	using TypeId = size_t;
	using ObjectId = uint64_t;

	using ComponentTypeId = TypeId;
	using ComponentId = ObjectId;

	static const ComponentId INVALID_COMPONENT_ID = std::numeric_limits<ComponentId>::max();

	using EntityTypeId = TypeId;
	using EntityId = ObjectId;

	static const EntityId INVALID_ENTITY_ID = std::numeric_limits<EntityId>::max();

	using SystemTypeId = TypeId;

	static const SystemTypeId INVALID_SYSTEM_TYPE_ID = std::numeric_limits<SystemTypeId>::max();
}
