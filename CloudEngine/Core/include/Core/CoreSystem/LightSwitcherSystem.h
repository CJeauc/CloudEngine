#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/LightComponent.h>

/*
This is a test system that makes attached light change color with keys

this is just a proof of concept to showcase the strength of the engine

please peek into the cpp to know the controls

key 1 = color.r --
key 2 = color.r ++
key 3 = color.g --
key 4 = color.g ++
key 5 = color.b --
key 6 = color.b ++
*/

namespace Core
{
	namespace Systems
	{
		using namespace Core;

		class CORE_API LightSwitcherSystem : public  System<LightSwitcherSystem>
		{
		public:
			LightSwitcherSystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Awake() override;
			void Update(double p_deltaTime) override;

		private:
			std::shared_ptr<Components::LightComponent> m_light;
			float m_switcherIncrement;
		};
	}
}