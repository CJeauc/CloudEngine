#include <Core/stdafx.h>
#include <Core/CoreSystem/InputTestSystem.h>

using namespace Core::Systems;

InputTestSystem::InputTestSystem(SystemPriority p_priority, double p_updateInterval_ms)
	: m_transform {nullptr}, m_speed {50}
{
}

void InputTestSystem::Update(double p_deltaTime)
{
	if (m_transform)
	{
		if (Input::GetKey(Key::KEY_K))
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(0.05f, 0, 0) * p_deltaTime * m_speed);
																												 
		if (Input::GetKey(Key::KEY_H))																			 
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(-0.05f, 0, 0) * p_deltaTime* m_speed );
																												 
		if (Input::GetKey(Key::KEY_U))																			 
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(0, 0, 0.05f) * p_deltaTime * m_speed);
																												
		if (Input::GetKey(Key::KEY_J))																			
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(0, 0, -0.05f) * p_deltaTime* m_speed );
																												
		if (Input::GetKey(Key::KEY_O))																			
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(0, 0.05f, 0) * p_deltaTime * m_speed );
																												
		if (Input::GetKey(Key::KEY_L))																			
			m_transform->SetPosition(m_transform->GetPosition() + CloudMath::Vector3f(0, -0.05f, 0)* p_deltaTime * m_speed);
	}
}

void InputTestSystem::AttachTransform(std::shared_ptr<Components::Transform> p_transform)
{
	m_transform = p_transform;
}
