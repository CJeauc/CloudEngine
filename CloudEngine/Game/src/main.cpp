#include <Core.h>
#include <Physic.h>
#include "MyEntity.h"
#include "Core/CoreComponent/Physic/BoxCollider.h"
#include "Core/CoreComponent/Physic/SphereCollider.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "DemoRotationSystem.h"
#include <Core/CoreComponent/CameraComponent.h>
#include <Core/CoreSystem/FPCameraSystem.h>
#include "Core/CoreComponent/GamePlay/FirstPersonController.h"
#include <Core/CoreSystem/GamePlay/FirstPersonControllerSystem.h>

int main()
{
	Core::CloudEngine engine;
	engine.Init(true);
	;
	auto cameraGo = Core::ECS::Get().CreateEntity<Core::Entities::GameObject>("GameCamera");
	auto cameraTransform = cameraGo->AddComponent<Core::Components::Transform>();
	//cameraTransform->SetPosition(CloudMath::Vector3f(0, 0, 0));

	auto cameraComponent = cameraGo->AddComponent<Core::Components::CameraComponent>(true);
	cameraComponent->Sensitivity(0.02f);
	
	auto fpCameraSystem = Core::ECS::Get().AddSystem<Core::Systems::FPCameraSystem>();
	Core::ECS::Get().SetSystemCore<Core::Systems::FPCameraSystem>();
	fpCameraSystem->AttachCamera(cameraComponent);

	//auto fpc = engine.CreateGameObject("FirstPersonC", CloudMath::Vector3f(0, 3, 10), "Sphere");
	//fpc->AddComponent<Core::Components::FirstPersonController>();
	//
	//auto fpCameraSystem = Core::ECS::Get().AddSystem<Core::Systems::FirstPersonControllerSystem>();

	/*Cubes*/
	 auto cube1 = engine.CreateCubeEntity("Cube1", { 1.5f, 1.f, 0.f });
	 cube1->AddComponent<Core::Components::BoxCollider>();

	auto cubeWithGravity = engine.CreateCubeEntity("cubeWithGravity", {0, 10, 0});
	// auto trans = cubeWithGravity->GetComponent<Core::Components::Transform>();
	// trans->SetScale({1.f, 2.f, 1.f});
	auto box = cubeWithGravity->AddComponent<Core::Components::BoxCollider>();
	auto rb = cubeWithGravity->AddComponent<Core::Components::RigidBody>(1);
	rb->SetConstraint({true, true, true}, {true, true, true});
	rb->GetPhysicObject()->GetRigidBody()->SetFriction(0.9f);

	auto rotor = engine.CreateCubeEntity("Rotor", { 5.f, 2.f, 0.f });
	auto transform = rotor->GetComponent<Core::Components::Transform>();
	rotor->AddComponent<Core::Components::BoxCollider>();
	transform->SetScale({ 1.f, 10.f, 10.f });

	auto plane = engine.CreateCubeEntity("Plane", CloudMath::Vector3f(0, -2, 0));
	plane->GetComponent<Core::Components::Transform>()->SetScale({ 50.f, 2.f, 50.f });
	plane->AddComponent<Core::Components::BoxCollider>(CloudMath::Vector3f{ 1.f, 1.f, 1.f });
	

	Core::SceneManagement::SceneManager::GetActiveScene()->AddNodeToParent(cube1, cubeWithGravity);

	engine.Awake();

	while (engine.Running())
	{
		// if (rb)
		// {
		// 	if (Core::Input::GetKeyDown(Core::Key::KEY_B))
		// 		rb->GetPhysicObject()->GetTransform()->SetPosition({0, 10, 0});
		//
		// 	if (Core::Input::GetKeyDown(Core::Key::KEY_C) && rb->IsGrounded())
		// 		rb->AddForce({0.f, 8.f, 0.f});
		//
		// 	if (Core::Input::GetKey(Core::Key::KEY_RIGHT))
		// 		rb->SetLinearVelocity({
		// 			(rb->GetLinearVelocity().x + 0.2f) <= 5.f ? (rb->GetLinearVelocity().x + 0.2f) : 5.f,
		// 			rb->GetLinearVelocity().y,
		// 			rb->GetLinearVelocity().z
		// 		});
		//
		// 	if (Core::Input::GetKey(Core::Key::KEY_LEFT))
		// 		rb->SetLinearVelocity({
		// 			(rb->GetLinearVelocity().x - 0.2f) >= -5.f ? (rb->GetLinearVelocity().x - 0.2f) : -5.f,
		// 			rb->GetLinearVelocity().y,
		// 			rb->GetLinearVelocity().z
		// 		});
		//
		// 	if (Core::Input::GetKey(Core::Key::KEY_DOWN))
		// 		rb->SetLinearVelocity({
		// 			rb->GetLinearVelocity().x,
		// 			rb->GetLinearVelocity().y,
		// 			(rb->GetLinearVelocity().z + 0.2f) <= 5.f ? (rb->GetLinearVelocity().z + 0.2f) : 5.f
		// 		});
		//
		// 	if (Core::Input::GetKey(Core::Key::KEY_UP))
		// 		rb->SetLinearVelocity({
		// 			rb->GetLinearVelocity().x,
		// 			rb->GetLinearVelocity().y,
		// 			(rb->GetLinearVelocity().z - 0.2f) >= -5.f ? (rb->GetLinearVelocity().z - 0.2f) : -5.f
		// 		});
		//
		// 	if (Core::Input::GetKeyUp(Core::Key::KEY_RIGHT))
		// 		rb->SetLinearVelocity({0.2f, rb->GetLinearVelocity().y, rb->GetLinearVelocity().z});
		// 	if (Core::Input::GetKeyUp(Core::Key::KEY_LEFT))
		// 		rb->SetLinearVelocity({-0.2f, rb->GetLinearVelocity().y, rb->GetLinearVelocity().z});
		// 	if (Core::Input::GetKeyUp(Core::Key::KEY_DOWN))
		// 		rb->SetLinearVelocity({rb->GetLinearVelocity().x, rb->GetLinearVelocity().y, 0.2f});
		// 	if (Core::Input::GetKeyUp(Core::Key::KEY_UP))
		// 		rb->SetLinearVelocity({rb->GetLinearVelocity().x, rb->GetLinearVelocity().y, -0.2f});
		// }

		engine.Frame();
	}

	return 0;
}
