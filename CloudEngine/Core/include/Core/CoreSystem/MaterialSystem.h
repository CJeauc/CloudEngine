#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/MaterialRenderer.h>

/*
Later this system will check all material components
validating input and data 
*/

namespace Core
{
	namespace Systems
	{
		class CORE_API MaterialSystem : public  System<MaterialSystem>
		{
		public:
			MaterialSystem(Core::SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void FixedUpdate(double p_fixedDeltaTime) override;
			void PreUpdate(double p_deltaTime) override;
			void Update(double p_deltaTime) override;
			void PostUpdate(double p_deltaTime) override;
		};
	}
}