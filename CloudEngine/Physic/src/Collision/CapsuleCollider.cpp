#include "Physic/stdafx.h"
#include "Physic/Collision/CapsuleCollider.h"

Physic::CapsuleCollider::CapsuleCollider(float p_radius, float p_height)
	: ACollider(new btCapsuleShape(p_radius, p_height), ShapeType::CAPSULE), m_radius(p_radius), m_height(p_height) { }

Physic::CapsuleCollider::~CapsuleCollider() { }

float Physic::CapsuleCollider::GetRadius() const
{
	return m_radius;
}

void Physic::CapsuleCollider::SetRadius(float p_radius)
{
	m_radius = p_radius;
	delete m_collisionShape;
	m_collisionShape = new btCapsuleShape(m_radius, m_height);

	resizedShape.Invoke();
}

float Physic::CapsuleCollider::GetHeight() const
{
	return m_height;
}

void Physic::CapsuleCollider::SetHeight(float p_height)
{
	m_height = p_height;
	delete m_collisionShape;
	m_collisionShape = new btCapsuleShape(m_radius, m_height);

	resizedShape.Invoke();
}

void Physic::CapsuleCollider::SetRadiusAndHeight(float p_radius, float p_height)
{
	m_radius = p_radius;
	m_height = p_height;
	delete m_collisionShape;
	m_collisionShape = new btCapsuleShape(m_radius, m_height);

	resizedShape.Invoke();
}

float Physic::CapsuleCollider::GetVerticalDistanceFromCenter() const
{
	return (m_height * 0.5) + m_radius;
}
