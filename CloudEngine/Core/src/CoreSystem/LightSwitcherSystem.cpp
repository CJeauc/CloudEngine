#include <Core/stdafx.h>
#include <Core/CoreSystem/LightSwitcherSystem.h>
#include <Core/ECS/ECS.h>
#include <Core/Engine/Input.h>

using namespace Core::Systems;

LightSwitcherSystem::LightSwitcherSystem(SystemPriority p_priority, double p_updateInterval_ms)
	: m_switcherIncrement(0.2f)
{
}

void LightSwitcherSystem::Awake()
{
	auto lights = ECS::Get().GetComponents<Components::LightComponent>();

	if (0 <lights.size())
		m_light = std::static_pointer_cast<Components::LightComponent>(lights.begin()->second);
	else
		LOG(Log::Warning(), "No Lights found to act On");
}

void LightSwitcherSystem::Update(double p_deltaTime)
{
	if (m_light)
	{
		CloudMath::Vector3f lightColor = m_light->GetLight()->Diffuse();

		if (Input::GetKeyDown(Key::KEY_1))
		{
			if (lightColor.x <= 0.0f)
				return;

			m_light->GetLight()->SetDiffuse(lightColor - CloudMath::Vector3f(m_switcherIncrement, 0, 0));
		}

		if (Input::GetKeyDown(Key::KEY_2))
		{
			if (lightColor.x >= 1.0f)
				return;
			m_light->GetLight()->SetDiffuse(lightColor + CloudMath::Vector3f(m_switcherIncrement, 0, 0));
		}

		if (Input::GetKeyDown(Key::KEY_3))
		{
			if (lightColor.y <= 0.0f)
				return;
			m_light->GetLight()->SetDiffuse(lightColor - CloudMath::Vector3f(0, m_switcherIncrement, 0));
		}

		if (Input::GetKeyDown(Key::KEY_4))
		{
			if (lightColor.y >= 1.0f)
				return;

			m_light->GetLight()->SetDiffuse(lightColor + CloudMath::Vector3f(0, m_switcherIncrement, 0));
		}

		if (Input::GetKeyDown(Key::KEY_5))
		{
			if (lightColor.z <= 0.0f)
				return;
			m_light->GetLight()->SetDiffuse(lightColor - CloudMath::Vector3f(0, 0, m_switcherIncrement));
		}

		if (Input::GetKeyDown(Key::KEY_6))
		{
			if (lightColor.z >= 1.0f)
				return;

			m_light->GetLight()->SetDiffuse(lightColor + CloudMath::Vector3f(0, 0, m_switcherIncrement));
		}
	}
}
