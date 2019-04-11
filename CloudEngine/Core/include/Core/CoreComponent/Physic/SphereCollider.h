#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Component/Component.h"
#include "Core/CoreComponent/Physic/ACollider.h"

namespace Core
{
	namespace Components
	{
		class CORE_API SphereCollider : public Component<SphereCollider>, public ACollider
		{
		public:
			SphereCollider(float p_radius = 1.f);
			~SphereCollider();

			float GetRadius() const;
			void SetRadius(float p_radius);

		protected:
			void Init() override;

		private:
			float m_radius;
		};
	}
}