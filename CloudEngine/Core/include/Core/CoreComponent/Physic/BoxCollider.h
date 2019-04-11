#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Component/Component.h"
#include "Core/CoreComponent/Physic/ACollider.h"

namespace Core
{
	namespace Components
	{
		class CORE_API BoxCollider : public Component<BoxCollider>, public ACollider
		{
		public:
			explicit BoxCollider(const CloudMath::Vector3f& p_boxExtents = { 1, 1, 1 });
			~BoxCollider();

			CloudMath::Vector3f GetBoxExtents() const;
			void SetBoxExtents(const CloudMath::Vector3f& p_boxExtents);

		protected:
			virtual void Init() override;

		private:
			CloudMath::Vector3f m_boxExtents;

		};
	}
}