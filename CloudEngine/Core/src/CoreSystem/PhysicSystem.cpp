#include <Core/stdafx.h>
#include <Core/CoreSystem/PhysicSystem.h>
#include "Core/ECS/ECS.h"
#include "Core/CoreComponent/Physic/RigidBody.h"

Core::Systems::PhysicSystem::PhysicSystem(SystemPriority p_priority,
                                          double p_updateInterval_ms)
	: System(p_priority, p_updateInterval_ms)
{
}

void Core::Systems::PhysicSystem::Awake() { }

void Core::Systems::PhysicSystem::FixedUpdate(double p_fixedDeltaTime)
{
	auto physicObjects = ECS::Get().GetComponents<Components::PhysicObject>();
	for (auto physicObjectIt : physicObjects)
	{
		auto rigidBody = std::static_pointer_cast<Components::PhysicObject>(physicObjectIt.second);
		rigidBody->RefreshRigidBodyData();
	}

	Cloud::Get().PhysicEngine()->Update(p_fixedDeltaTime);

	for (auto physicObjectIt : physicObjects)
	{
		auto rigidBody = std::static_pointer_cast<Components::PhysicObject>(physicObjectIt.second);
		rigidBody->RefreshTransformData();
		rigidBody->RefreshCollisionStates();
	}
}
