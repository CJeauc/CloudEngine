#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/BoxCollider.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Physic/Collision/BoxCollider.h"
#include "Core/ECS/ECS.h"

Core::Components::BoxCollider::BoxCollider(const CloudMath::Vector3f& p_boxExtents)
	: m_boxExtents(p_boxExtents)
{
}

Core::Components::BoxCollider::~BoxCollider()
{
}

CloudMath::Vector3f Core::Components::BoxCollider::GetBoxExtents() const
{
	return dynamic_cast<Physic::BoxCollider*>(m_physicObject->GetCollider())->GetBoxExtents();
}

void Core::Components::BoxCollider::SetBoxExtents(const CloudMath::Vector3f& p_boxExtents)
{
	m_boxExtents = p_boxExtents;
	dynamic_cast<Physic::BoxCollider*>(m_physicObject->GetCollider())->SetBoxExtents(p_boxExtents);
}

void Core::Components::BoxCollider::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	m_physicObject = owner->GetComponent<PhysicObject>();
	if (!m_physicObject)
		m_physicObject = owner->AddComponent<PhysicObject>(new Physic::BoxCollider(m_boxExtents));
	else
		m_physicObject->SetCollider(new Physic::BoxCollider(m_boxExtents));
}
