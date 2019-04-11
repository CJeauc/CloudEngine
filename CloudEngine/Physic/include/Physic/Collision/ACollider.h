#pragma once

#include "Physic/PhysicAPI.h"
#include <bullet/btBulletCollisionCommon.h>
#include "CloudMath.h"

namespace Physic
{
	class PHYSIC_API ACollider
	{
	public:
		enum class ShapeType : char
		{
			SPHERE = 'S',
			BOX = 'B',
			CAPSULE = 'C',
			MESH = 'M',
			INVALID = -1,
		};

	protected:
		explicit ACollider(btCollisionShape* p_collisionShape, ShapeType p_shapeType);

	public:
		virtual ~ACollider();

		btCollisionShape* GetShape() const;
		ShapeType GetShapeType() const;

		void SetScale(CloudMath::Vector3f p_scale);
		CloudMath::Vector3f GetScale() const;

		virtual float GetVerticalDistanceFromCenter() const = 0;

	protected:
		virtual void ApplyNewScale();

	public:
		Tools::Event<> resizedShape;

	protected:
		const ShapeType m_shapeType;
		CloudMath::Vector3f m_scale;
		btCollisionShape* m_collisionShape;
	};
}
