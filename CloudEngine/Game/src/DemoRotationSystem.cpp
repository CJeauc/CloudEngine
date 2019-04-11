#include <Core/stdafx.h>
#include "DemoRotationSystem.h"

DemoRotationSystem::DemoRotationSystem(Core::SystemPriority p_priority, double p_updateInterval_ms)
{
}

void DemoRotationSystem::Update(double p_deltaTime)
{
	for (auto transform : m_transforms)
	{
		transform->Rotate(CloudMath::Vector3f(0.5f * (float)p_deltaTime, (float)p_deltaTime, 0));
	}
}

void DemoRotationSystem::AddTransform(std::shared_ptr<Core::Components::Transform> p_transform)
{
	m_transforms.push_back(p_transform);
}
