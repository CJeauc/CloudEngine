#pragma once

#include "Core/CoreAPI.h"
#include "AEntity.h"
#include "Core/Engine/Cloud.h"

namespace Core::Entities
{
	class GameObject;
	class Daemon;
}

namespace Core
{
	template <typename T>
	class Entity : public AEntity
	{
		// Only the EntityManager have the right to destroy an Entity
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;

	public:
		Entity() = default;
		~Entity() = default;

		EntityTypeId GetEntityTypeId() const override { return StaticEntityTypeId; }

	public:
		static const EntityTypeId StaticEntityTypeId;
	};

	template <>
	const EntityTypeId Entity<Entities::GameObject>::StaticEntityTypeId = *Cloud::Get().FamilyType<AEntity>()->Get<Entities::GameObject>("GameObject");

	template <>
	const EntityTypeId Entity<Entities::Daemon>::StaticEntityTypeId = *Cloud::Get().FamilyType<AEntity>()->Get<Entities::Daemon>("Daemon");

	// set unique type id for this Entity<T>
	template <typename T>
	const EntityTypeId Entity<T>::StaticEntityTypeId = *Cloud::Get().FamilyType<AEntity>()->Get<T>(GetNameFromType<T>());
}
