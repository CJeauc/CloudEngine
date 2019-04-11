#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/CameraComponent.h>
#include <CloudMath.h>
#include <Core/Engine/Input.h>

/*
 If this system is linked to a camera it will allow moving the camera in a first person manner
*/

namespace Core
{
	namespace Systems
	{
		class CORE_API FPCameraSystem : public Core::System<FPCameraSystem>
		{
		public:
			FPCameraSystem(Core::SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Update(double p_deltaTime) override;
			void PreUpdate(double p_deltaTime) override;

			void AttachCamera(std::shared_ptr<Core::Components::CameraComponent> p_camera);

		private:
			std::shared_ptr<Core::Components::CameraComponent> m_camera;

			float m_lastMouseX;
			float m_lastMouseY;

			bool m_firstMouse = true;
		};
	}
}
