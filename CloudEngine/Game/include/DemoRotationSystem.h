#pragma once

#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/Transform.h>
#include <CloudMath.h>
#include <Core/Engine/Input.h>

/*
This is a test system that makes attached transforms rotate

this is just a proof of concept to showcase the strength of the engine
*/

		class DemoRotationSystem : public Core:: System<DemoRotationSystem>
		{
		public:
			DemoRotationSystem(Core::SystemPriority p_priority = Core::SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Update(double p_deltaTime) override;

			void AddTransform(std::shared_ptr<Core::Components::Transform> p_transform);

		private:
			std::vector<std::shared_ptr<Core::Components::Transform>> m_transforms{};
		};
