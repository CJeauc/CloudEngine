#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>

/*
The Camera Component hold a referemce to a rendering camera
The component it self only has data such as position and if this camera is main

This component Only has the basic functionality for our first prototype to work
Later on, this component will have all camera data such as yaw, pitch, movementspeed ...

This component is manager by the CameraSystem
*/
namespace Core
{
	namespace Components
	{
		class CORE_API CameraComponent : public Component<CameraComponent>
		{
		public:
			CameraComponent(bool p_mainCamera = false, float p_speed = 5.0f, float p_sensitivity = 0.3f, float p_zoom = 45.f);
			~CameraComponent();
			
			bool IsMainCamera();
			void SetMainCamera(bool p_mainCamera);

			float Speed() const { return m_movementSpeed; }
			float Sensitivity() const { return m_sensitivity; }
			float Zoom() const { return m_zoom; }
			float Yaw() const {return m_yaw; }
			float Pitch() const { return m_pitch; }

			void Speed(float p_speed) { m_movementSpeed = p_speed; }
			void Sensitivity(float p_sensitivity) { m_sensitivity = p_sensitivity; }
			void Zoom(float p_zoom) { m_zoom = p_zoom; }
			void Yaw(float p_yaw)
			{
				m_yaw = p_yaw;
				if (m_yaw > 89.99f)
					m_yaw = 89.99f;
				if (m_yaw < -89.99f)
					m_yaw = -89.99f;
			}
			void Pitch(float p_pitch) { m_pitch = p_pitch; }

		private:
			float m_movementSpeed;
			float m_sensitivity;
			float m_zoom;
			bool m_mainCamera;

			float m_yaw{ 0 };
			float m_pitch{ 180 };

		};
	}
}