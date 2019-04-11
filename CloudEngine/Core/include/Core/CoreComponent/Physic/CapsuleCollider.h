#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Component/Component.h"
#include "Core/CoreComponent/Physic/ACollider.h"

namespace Core
{
	namespace Components
	{
		class CORE_API CapsuleCollider : public Component<CapsuleCollider>, public ACollider
		{
		public:
			explicit CapsuleCollider(float p_radius = 1.f, float p_height = 1.f);
			~CapsuleCollider();

			float GetRadius() const;
			void SetRadius(float p_radius);

			float GetHeight() const;
			void SetHeight(float p_height);

			void SetRadiusAndHeight(float p_radius, float p_height);

		protected:
			void Init() override;

		private:
			float m_radius;
			float m_height;
		};
	}
}