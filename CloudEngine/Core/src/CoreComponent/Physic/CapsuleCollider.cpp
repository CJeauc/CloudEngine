#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Physic/Collision/CapsuleCollider.h"
#include "Core/ECS/ECS.h"

Core::Components::CapsuleCollider::CapsuleCollider(float p_radius, float p_height)
	: m_radius(p_radius), m_height(p_height)
{
	
}

Core::Components::CapsuleCollider::~CapsuleCollider()
{
	
}

float Core::Components::CapsuleCollider::GetRadius() const
{
	return m_radius;
}

void Core::Components::CapsuleCollider::SetRadius(float p_radius)
{
	m_radius = p_radius;
	dynamic_cast<Physic::CapsuleCollider*>(m_physicObject->GetCollider())->SetRadius(p_radius);
}
float Core::Components::CapsuleCollider::GetHeight() const
{
	return m_height;
}
void Core::Components::CapsuleCollider::SetHeight(float p_height)
{	
	m_height = p_height;
	dynamic_cast<Physic::CapsuleCollider*>(m_physicObject->GetCollider())->SetRadius(p_height);
}
void Core::Components::CapsuleCollider::SetRadiusAndHeight(float p_radius, float p_height)
{
	m_radius = p_radius;
	m_height = p_height;
	dynamic_cast<Physic::CapsuleCollider*>(m_physicObject->GetCollider())->SetRadiusAndHeight(p_radius, p_height);
}

void Core::Components::CapsuleCollider::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	m_physicObject = owner->GetComponent<PhysicObject>();
	if (!m_physicObject)
		m_physicObject = owner->AddComponent<PhysicObject>(new Physic::CapsuleCollider(m_radius, m_height));
	else
		m_physicObject->SetCollider(new Physic::CapsuleCollider(m_radius, m_height));
}
