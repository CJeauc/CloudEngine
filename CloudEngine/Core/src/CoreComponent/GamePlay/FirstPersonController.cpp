#include "Core/stdafx.h"
#include "Core/CoreComponent/GamePlay/FirstPersonController.h"
#include "Core/ECS/ECS.h"
#include "Core/CoreEntity/GameObject.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "Core/CoreSystem/FPCameraSystem.h"
#include "Core/Scene/SceneManager.h"

using namespace Core::Components;

void FirstPersonController::Init()
{
	auto owner = std::static_pointer_cast<Entities::GameObject>(Core::ECS::Get().GetEntity(m_ownerId));

	m_rigidBody = owner->AddComponent<Components::RigidBody>(1);
	m_rigidBody->GetPhysicObject()->GetRigidBody()->SetFriction(1.f);
	// m_rigidBody->SetConstraint({true, true, true }, {false, true, false});
	owner->AddComponent<Components::CapsuleCollider>(1, 2);

	auto cameraGo = Core::ECS::Get().CreateEntity<Core::Entities::GameObject>("Camera");
	cameraGo->AddComponent<Core::Components::Transform>();
	m_cameraComponent = cameraGo->AddComponent<Core::Components::CameraComponent>(true);
	m_cameraComponent->Sensitivity(0.02f);

	SceneManagement::SceneManager::GetActiveScene()->AddNodeToParent(cameraGo, owner);
}

std::shared_ptr<RigidBody> FirstPersonController::GetRigidBody() const
{
	return m_rigidBody;
}

std::shared_ptr<CameraComponent> FirstPersonController::GetCamera() const
{
	return m_cameraComponent;
}
