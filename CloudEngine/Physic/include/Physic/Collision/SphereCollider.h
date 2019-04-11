#pragma once

#include "ACollider.h"

namespace Physic
{
	class PHYSIC_API SphereCollider : public ACollider
	{
	public:
		explicit SphereCollider(float p_radius = 1.f);
		~SphereCollider();

		float GetRadius() const;
		void SetRadius(float p_radius);

		float GetVerticalDistanceFromCenter() const override;

	private:
		float m_radius;
	};
}
