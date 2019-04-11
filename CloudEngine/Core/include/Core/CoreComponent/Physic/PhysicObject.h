#pragma once

#include "Core/ECS/Component/Component.h"
#include "Core/CoreAPI.h"
#include "Physic/Dynamics/RigidBody.h"
#include "Physic/Collision/ACollider.h"

namespace Core
{
	namespace Components
	{
		class ACollider;

		class CORE_API PhysicObject : public Component<PhysicObject>
		{
			friend class ::Core::Systems::PhysicSystem;
			friend class ::Core::Components::ACollider;

		public:
			PhysicObject();
			explicit PhysicObject(float p_mass);
			explicit PhysicObject(Physic::ACollider* p_collider);
			~PhysicObject();

			void SetCollider(Physic::ACollider* p_collider);

			void CreateRigidBody(float p_mass = 1);

			Physic::ACollider* GetCollider() const;
			Physic::RigidBody* GetRigidBody() const;

			std::shared_ptr<Transform> GetTransform() const;
			void DisableRigidBody();

			void SetIsTrigger(bool p_isTrigger);
			bool IsTrigger() const;

			void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const override;
			void DeSerialize(TinyXML2::XMLElement* p_componentNode) override;

		protected:
			void Init() override;

		private:
			void RefreshRigidBodyData();
			void RefreshTransformData();
			void RefreshCollisionStates();

			void OnTransformChangedEvent();

			void SetupColliderAndRigidBody();

			void SubscribeToCollisionEvents();
			void UnSubscribeToCollisionEvents();

			void OnCollision(Physic::RigidBody* p_otherRigidBody);
			void OnTrigger(Physic::RigidBody* p_otherRigidBody);

			void OnFillCollisionsInfo(Collision& p_collisionInfo);

		private:
			Physic::ACollider* m_collider = nullptr;
			Physic::RigidBody* m_rigidBody = nullptr;

			bool m_haveRigidBodyComponent {false};
			bool m_haveColliderComponent {false};

			std::shared_ptr<Transform> m_transform;
			uint16_t m_transformChangedEvent;

			float m_mass;

			struct
			{
				uint16_t onCollision {0};
				uint16_t onTrigger {0};
				uint16_t onFillCollisionsInfo {0};

				Tools::Event<Collision> onCollisionEnter;
				Tools::Event<Collision> onCollisionStay;
				Tools::Event<Collision> onCollisionExit;
				std::unordered_map<std::string, std::pair<bool, Physic::RigidBody*>> collisionState {};

				Tools::Event<std::shared_ptr<Components::ACollider>> onTriggerEnter;
				Tools::Event<std::shared_ptr<Components::ACollider>> onTriggerStay;
				Tools::Event<std::shared_ptr<Components::ACollider>> onTriggerExit;
				std::unordered_map<std::string, std::pair<bool, Physic::RigidBody*>> triggerState {};
			} m_collisionEvents;
		};
	}
}
