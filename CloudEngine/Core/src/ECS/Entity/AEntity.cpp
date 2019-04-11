#include "Core/stdafx.h"
#include "Core/ECS/Entity/AEntity.h"

Core::AEntity::AEntity()
	: m_entityId(0), m_active(true) { }

void Core::AEntity::SetActive(bool p_active)
{
	if (m_active == p_active)
		return;

	p_active ? OnEnable() : OnDisable();

	m_active = p_active;
}

std::vector<std::shared_ptr<Core::AComponent>> Core::AEntity::GetComponents()
{
	return m_componentManagerInstance->GetComponentsOfEntity(m_entityId);
}

