#pragma once

#include "Core/CoreAPI.h"
#include "Core/CoreComponent/Physic/PhysicObject.h"

namespace Core
{
	namespace Components
	{
		// Add this component on non physic objects to use raycast on them
		class CORE_API RayCastEnabler : Component<RayCastEnabler>
		{
		public:
			RayCastEnabler();

		protected:
			void Init() override;

		private:
			std::shared_ptr<PhysicObject> m_physicObject;
		};
	}
}
