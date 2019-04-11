#include "Core/stdafx.h"
#include "Core/CoreSystem/GamePlay/FirstPersonControllerSystem.h"
#include "Core/CoreComponent/GamePlay/FirstPersonController.h"
#include "Core/ECS/ECS.h"
#include "Core/Engine/Input.h"
#include "Core/CoreComponent/Physic/RigidBody.h"

using namespace Core::Systems;

void FirstPersonControllerSystem::PreUpdate(double p_deltaTime)
{
	auto firstPersonControllers = ECS::Get().GetComponents<Components::FirstPersonController>();
	for (auto firstPersonController : firstPersonControllers)
	{
		auto firstPCC = std::static_pointer_cast<Components::FirstPersonController>(firstPersonController.second);
		if (firstPCC->m_firstMouse)
		{
			firstPCC->m_lastMouseX = Input::MouseX();
			firstPCC->m_lastMouseY = Input::MouseY();
			firstPCC->m_firstMouse = false;
			return;
		}

		auto rigidBody = firstPCC->GetRigidBody();
		if (rigidBody)
		{
			auto speed = firstPCC->GetCamera()->Speed() * static_cast<float>(p_deltaTime);

			auto transform = rigidBody->GetPhysicObject()->GetTransform();

			if (Core::Input::GetKeyDown(Core::Key::KEY_SPACE) && rigidBody->IsGrounded())
				rigidBody->AddForce({0.f, 8.f, 0.f});

			if (Core::Input::GetKey(Core::Key::KEY_D))
				rigidBody->SetLinearVelocity(rigidBody->GetLinearVelocity() + transform->GetWorldRight() * speed);

			if (Core::Input::GetKey(Core::Key::KEY_A))
				rigidBody->SetLinearVelocity(rigidBody->GetLinearVelocity() + transform->GetWorldRight() * -speed);

			if (Core::Input::GetKey(Core::Key::KEY_W))
				rigidBody->SetLinearVelocity(
					rigidBody->GetLinearVelocity() + transform->GetWorldRight().CrossProduct({0, 1, 0}) * -speed);

			if (Core::Input::GetKey(Core::Key::KEY_S))
				rigidBody->SetLinearVelocity(
					rigidBody->GetLinearVelocity() + transform->GetWorldRight().CrossProduct({0, 1, 0}) * speed);

			if (Core::Input::GetKey(Core::Key::KEY_BACKSPACE))
				rigidBody->SetLinearVelocity({0, 0, 0});

			firstPCC->GetCamera()->Yaw(
				firstPCC->GetCamera()->Yaw() + (Input::MouseY() - firstPCC->m_lastMouseY) * firstPCC
				                                                                            ->GetCamera()->
				                                                                            Sensitivity());
			firstPCC->GetCamera()->Pitch(
				firstPCC->GetCamera()->Pitch() + (firstPCC->m_lastMouseX - Input::MouseX()) * firstPCC
				                                                                              ->GetCamera()->
				                                                                              Sensitivity());

			if (Input::ShouldUpdateMouse())
				transform->SetRotation(CloudMath::Vector3f{
					firstPCC->GetCamera()->Yaw(), firstPCC->GetCamera()->Pitch(), 0.f
				});

			firstPCC->m_lastMouseX = Input::MouseX();
			firstPCC->m_lastMouseY = Input::MouseY();
		}
	}
}
