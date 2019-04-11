#include <Core/stdafx.h>
#include <Core/CoreComponent/LightComponent.h>
#include "Core/ECS/ECS.h"
#include "Core/CoreComponent/Transform.h"

using namespace Core::Components;

Core::Components::LightComponent::LightComponent()
{
	m_light = std::make_shared<Rendering::Light>();
}

Core::Components::LightComponent::~LightComponent()
{
}

void LightComponent::SetPosition(const CloudMath::Vector3f& p_position)
{
	if(m_light)
		m_light->SetPosition(p_position);
}

void LightComponent::SetColor(const CloudMath::Vector3f& p_color)
{
	if (m_light)
		m_light->SetDiffuse(p_color);
}

std::shared_ptr<Rendering::Light> Core::Components::LightComponent::GetLight()
{
	return m_light;
}

void LightComponent::Init()
{
	auto owner = ECS::Get().m_entityManager->GetEntity(m_ownerId);
	owner->AddComponent<Transform>();
}
