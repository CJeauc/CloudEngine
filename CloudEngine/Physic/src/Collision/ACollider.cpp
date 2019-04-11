#include "Physic/stdafx.h"
#include "Physic/Collision/ACollider.h"
#include "Physic/Math/Conversion.h"

Physic::ACollider::ACollider(btCollisionShape* p_collisionShape, ShapeType p_shapeType)
	: m_shapeType(p_shapeType), m_scale{1, 1, 1}, m_collisionShape{p_collisionShape} {}

Physic::ACollider::~ACollider()
{
	delete m_collisionShape;
}

btCollisionShape* Physic::ACollider::GetShape() const
{
	return m_collisionShape;
}

Physic::ACollider::ShapeType Physic::ACollider::GetShapeType() const
{
	return m_shapeType;
}

void Physic::ACollider::SetScale(CloudMath::Vector3f p_scale)
{
	if ((m_scale - p_scale).Length() > 0.01f)
	{
		m_scale = std::move(p_scale);
		ApplyNewScale();
	}
}

CloudMath::Vector3f Physic::ACollider::GetScale() const
{
	return m_scale;
}

void Physic::ACollider::ApplyNewScale()
{
	if (m_collisionShape)
	{
		m_collisionShape->setLocalScaling(ToBtVec(m_scale));
		resizedShape.Invoke();
	}
}
