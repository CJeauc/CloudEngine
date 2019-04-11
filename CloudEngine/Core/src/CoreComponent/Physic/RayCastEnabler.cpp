#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/RayCastEnabler.h"
#include "Core/ECS/ECS.h"

Core::Components::RayCastEnabler::RayCastEnabler()
{
	
}

void Core::Components::RayCastEnabler::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	auto physicObject = owner->GetComponent<PhysicObject>();
	if (!physicObject)
	{
		physicObject = owner->AddComponent<PhysicObject>(nullptr);
		physicObject->GetRigidBody()->SetKinematic(true);
	}
}
