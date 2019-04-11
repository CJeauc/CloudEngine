#include "Physic/stdafx.h"
#include "Physic/Collision/SphereCollider.h"

Physic::SphereCollider::SphereCollider(float p_radius)
	: ACollider(new btSphereShape(p_radius), ShapeType::SPHERE), m_radius{p_radius}
{
}

Physic::SphereCollider::~SphereCollider()
{
}

float Physic::SphereCollider::GetRadius() const
{
	return m_radius;
}


void Physic::SphereCollider::SetRadius(float p_radius)
{
	m_radius = p_radius;
	delete m_collisionShape;
	m_collisionShape = new btSphereShape(p_radius);

	resizedShape.Invoke();
}

float Physic::SphereCollider::GetVerticalDistanceFromCenter() const
{
	return m_radius;
}

