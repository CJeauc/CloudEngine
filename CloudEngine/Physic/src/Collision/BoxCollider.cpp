#include "Physic/stdafx.h"
#include "Physic/Collision/BoxCollider.h"

Physic::BoxCollider::BoxCollider(CloudMath::Vector3f p_boxExtents)
	: ACollider(new btBoxShape({p_boxExtents.x * 0.5f, p_boxExtents.y * 0.5f, p_boxExtents.z * 0.5f}), ShapeType::BOX),
	  m_boxHalfExtents{p_boxExtents.x * 0.5f, p_boxExtents.y * 0.5f, p_boxExtents.z * 0.5f}
{
}

Physic::BoxCollider::~BoxCollider() {}

CloudMath::Vector3f Physic::BoxCollider::GetBoxExtents() const
{
	return (m_boxHalfExtents * 2);
}

void Physic::BoxCollider::SetBoxExtents(const CloudMath::Vector3f& p_boxExtents)
{
	m_boxHalfExtents = p_boxExtents;
	delete m_collisionShape;
	m_collisionShape = new btBoxShape({ p_boxExtents.x * 0.5f, p_boxExtents.y * 0.5f, p_boxExtents.z * 0.5f });

	resizedShape.Invoke();
}

float Physic::BoxCollider::GetVerticalDistanceFromCenter() const
{
	return m_boxHalfExtents.y;
}
