#include <Core/stdafx.h>
#include <Core/CoreSystem/FPCameraSystem.h>
#include <Core/ECS/ECS.h>
#include <Core/CoreComponent/Transform.h>

using namespace Core::Systems;

FPCameraSystem::FPCameraSystem(Core::SystemPriority p_priority, double p_updateInterval_ms)
	: m_lastMouseX(0), m_lastMouseY(0)
{
}

void FPCameraSystem::PreUpdate(double p_deltaTime)
{
	if (m_firstMouse)
	{
		m_lastMouseX = Input::MouseX();
		m_lastMouseY = Input::MouseY();
		m_firstMouse = false;
		return;
	}

	if (m_camera)
	{
		float xOffset = m_lastMouseX - Input::MouseX();
		float yOffset = Input::MouseY() - m_lastMouseY;

		m_camera->Yaw(m_camera->Yaw() + yOffset * m_camera->Sensitivity());
		m_camera->Pitch(m_camera->Pitch() + xOffset * m_camera->Sensitivity());

		auto owner = ECS::Get().GetEntity(m_camera->GetOwnerId());
		auto transform = owner->GetComponent<Core::Components::Transform>();

		if (Input::GetKey(Key::KEY_W))
		{
			transform->SetPosition(transform->GetPosition() + (transform->GetFront() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::GetKey(Key::KEY_S))
		{
			transform->SetPosition(transform->GetPosition() - (transform->GetFront() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::GetKey(Key::KEY_D))
		{
			transform->SetPosition(transform->GetPosition() + (transform->GetRight() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::GetKey(Key::KEY_A))
		{
			transform->SetPosition(transform->GetPosition() - (transform->GetRight() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::GetKey(Key::KEY_SPACE))
		{
			transform->SetPosition(transform->GetPosition() + (transform->GetUp() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::GetKey(Key::KEY_LEFT_SHIFT))
		{
			transform->SetPosition(transform->GetPosition() - (transform->GetUp() * m_camera->Speed() * p_deltaTime));
		}

		if (Input::ShouldUpdateMouse())
		{
			transform->SetRotation(CloudMath::Vector3f{ m_camera->Yaw(), m_camera->Pitch(), 0.f });
		}

		m_lastMouseX = Input::MouseX();
		m_lastMouseY = Input::MouseY();
	}
}

void FPCameraSystem::Update(double p_deltaTime)
{
}

void FPCameraSystem::AttachCamera(std::shared_ptr<Core::Components::CameraComponent> p_camera)
{
	m_camera = p_camera;
}
