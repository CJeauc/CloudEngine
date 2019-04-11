#include "Core/stdafx.h"
#include "Core/ECS/Component/AComponent.h"

using namespace Core;

AComponent::AComponent()
	: m_active(true) { }

const ComponentId& AComponent::GetComponentId() const
{
	return m_componentId;
}

const EntityId& AComponent::GetOwnerId() const
{
	return m_ownerId;
}

void AComponent::SetActive(const bool p_active)
{
	m_active = p_active;
}

bool AComponent::IsActive() const
{
	return m_active;
}
