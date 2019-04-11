#pragma once

#include "Core/CoreAPI.h"
#include "Core/CoreComponent/Physic/PhysicObject.h"

namespace Core
{
	namespace Components
	{
		class ACollider;
	}
	struct CORE_API Collision
	{
		std::shared_ptr<Entities::GameObject> gameObject{ nullptr };
		std::shared_ptr<Components::ACollider> collider{ nullptr };
		std::shared_ptr<Components::RigidBody> rigidBody{ nullptr };
		std::shared_ptr<Components::Transform> transform{ nullptr };
	};

	namespace Components
	{
		class CORE_API ACollider
		{
		protected:
			ACollider() = default;

		public:
			virtual ~ACollider();

			Physic::ACollider* GetCollider() const;
			std::shared_ptr<PhysicObject> GetPhysicObject() const;

			void SetIsTrigger(bool p_isTrigger);
			bool IsTrigger() const;

			Tools::Event<Collision>& OnCollisionEnter();
			Tools::Event<Collision>& OnCollisionStay();
			Tools::Event<Collision>& OnCollisionExit();

			Tools::Event<std::shared_ptr<Components::ACollider>>& OnTriggerEnter();
			Tools::Event<std::shared_ptr<Components::ACollider>>& OnTriggerStay();
			Tools::Event<std::shared_ptr<Components::ACollider>>& OnTriggerExit();

		protected:
			std::shared_ptr<PhysicObject> m_physicObject;
		};
	}
}
