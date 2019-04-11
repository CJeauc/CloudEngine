#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>
#include "Core/CoreComponent/CameraComponent.h"

namespace Core
{
	namespace Systems
	{
		class FirstPersonControllerSystem;
	}

	namespace Components
	{
		class CORE_API FirstPersonController : public Component<FirstPersonController>
		{
			friend Systems::FirstPersonControllerSystem;

		public:
			FirstPersonController() = default;
			~FirstPersonController() = default;

			void Init() override;
			std::shared_ptr<Components::RigidBody> GetRigidBody() const;
			std::shared_ptr<Components::CameraComponent> GetCamera() const;

		private:
			std::shared_ptr<Components::RigidBody> m_rigidBody;
			std::shared_ptr<Components::CameraComponent> m_cameraComponent;

			float m_lastMouseX{0.f};
			float m_lastMouseY{0.f};

			bool m_firstMouse = true;
		};
	}
}
