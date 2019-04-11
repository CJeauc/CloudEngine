#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include "ACollider.h"

namespace Physic
{
	class PHYSIC_API CapsuleCollider : public ACollider
	{
	public:
		explicit CapsuleCollider(float p_radius = 1.f, float p_height = 1.f);
		~CapsuleCollider();

		float GetRadius() const;
		void SetRadius(float p_radius);

		float GetHeight() const;
		void SetHeight(float p_height);

		void SetRadiusAndHeight(float p_radius, float p_height);

		float GetVerticalDistanceFromCenter() const override;

	private:
		float m_radius;
		float m_height;
	};
}