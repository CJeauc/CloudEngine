#pragma once

#include <Core/ECS/System/System.h>

namespace Core
{
	namespace Systems
	{
		class CORE_API PhysicSystem : public System<PhysicSystem>
		{
		public:
			explicit PhysicSystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
			             double p_updateInterval_ms = -1.0);

			void Awake() override;
			void FixedUpdate(double p_fixedDeltaTime) override;

		private:
		};
	}
}
