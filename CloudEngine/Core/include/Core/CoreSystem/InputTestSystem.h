#pragma once

#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/Transform.h>
#include <CloudMath.h>
#include <Core/Engine/Input.h>

/*
This is a test system that makes attached transforms move with keys

this is just a proof of concept to showcase the strength of the engine

please peek into the cpp to know the controls
*/

namespace Core
{
	namespace Systems
	{
		using namespace Core;

		class CORE_API InputTestSystem : public Core:: System<InputTestSystem>
		{
		public:
			InputTestSystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Update(double p_deltaTime) override;

			void AttachTransform(std::shared_ptr<Components::Transform> p_transform);

		private:
			std::shared_ptr<Components::Transform> m_transform;
			float m_speed;
		};
	}
}