#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/SphereCollider.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Physic/Collision/SphereCollider.h"
#include "Core/ECS/ECS.h"

Core::Components::SphereCollider::SphereCollider(float p_radius)
	: m_radius(p_radius)
{
}

Core::Components::SphereCollider::~SphereCollider()
{
	
}

float Core::Components::SphereCollider::GetRadius() const
{
	return m_radius;
}

void Core::Components::SphereCollider::SetRadius(float p_radius)
{
	dynamic_cast<Physic::SphereCollider*>(m_physicObject->GetCollider())->SetRadius(p_radius);
}

void Core::Components::SphereCollider::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	m_physicObject = owner->GetComponent<PhysicObject>();
	if (!m_physicObject)
		m_physicObject = owner->AddComponent<PhysicObject>(new Physic::SphereCollider(m_radius));
	else
		m_physicObject->SetCollider(new Physic::SphereCollider(m_radius));
}
