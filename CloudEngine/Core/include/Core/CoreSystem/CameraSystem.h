#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/CameraComponent.h>
#include <Core/CoreComponent/UniformRendering.h>

/*
This system is responsible for the camera, its finds the main camera
and then sets values on the camera component
it then sends this data to whome it needs to : other dependent systems
For now we only consider the first main camera we encouter
When we will have an event system
setting a camera to main will trigger assigning the new camera as main
*/

namespace Core
{
	namespace Systems
	{
		class CORE_API CameraSystem : public Core:: System<CameraSystem>
		{
		public:
			CameraSystem(Core::SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Awake() override;
			void PreUpdate(double p_deltaTime) override;
			void Update(double p_deltaTime) override;

			std::shared_ptr<Core::Components::CameraComponent> GetMainCamera();

		private:
			std::shared_ptr<Core::Components::UniformRendering> m_uniformRendering;
			std::shared_ptr<Core::Components::CameraComponent> m_mainCamera;
		};
	}
}