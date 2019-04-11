#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include "ACollider.h"

namespace Physic
{
	class PHYSIC_API BoxCollider : public ACollider
	{
	public:
		explicit BoxCollider(CloudMath::Vector3f p_boxExtents = {1, 1, 1});
		~BoxCollider();

		CloudMath::Vector3f GetBoxExtents() const;
		void SetBoxExtents(const CloudMath::Vector3f& p_boxExtents);

		float GetVerticalDistanceFromCenter() const override;

	private:
		CloudMath::Vector3f m_boxHalfExtents;
	};
}
