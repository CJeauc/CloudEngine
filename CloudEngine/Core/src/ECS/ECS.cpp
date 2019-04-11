#include "Core/stdafx.h"
#include "Core/ECS/ECS.h"
#include <Core/CoreEntity/Daemon.h>
#include <Core/CoreEntity/GameObject.h>

namespace Core
{
	ECS::ECS()
	{
		m_componentManager = std::make_shared<ComponentManager>();
		m_entityManager = std::make_unique<EntityManager>(m_componentManager);
		m_systemManager = std::make_unique<SystemManager>();
	}

	ECS& ECS::Get()
	{
		static ECS instance;
		return instance;
	}

	void ECS::Clear()
	{
		m_entityManager->Clear<Entities::Daemon, Entities::GameObject>();
		m_systemManager->Clear();
	}

	std::shared_ptr<AEntity> ECS::GetOwner(std::shared_ptr<AComponent> p_component)
	{
		return p_component ? m_entityManager->GetEntity(p_component->GetOwnerId()) : nullptr;
	}

	std::shared_ptr<AEntity> ECS::GetEntity(EntityId p_entityId)
	{
		return m_entityManager->GetEntity(p_entityId);
	}

	void ECS::Awake()
	{
		m_systemManager->Awake();
	}
}
