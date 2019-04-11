#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <Tools.h>
#include "Physic/PhysicAPI.h"
#include "Physic/Collision/ACollider.h"
#include "Physic/Collision/SphereCollider.h"
#include "CloudMath/Matrix/Matrix4.h"

namespace Core
{
	struct Collision;
}

namespace Physic
{
	enum class CollisionDetection : uint8_t
	{
		DISCRETE = 0,
		CONTINUOUS,
	};

	class PHYSIC_API RigidBody
	{
	public:
		explicit RigidBody(ACollider* p_collider = new SphereCollider(),
		                   CloudMath::Matrix4f p_transform = CloudMath::Matrix4f::Identity,
		                   float p_mass = 0.f,
		                   float p_friction = 0.5f);
		~RigidBody();

		bool operator ==(const RigidBody& p_other) const;

		btRigidBody* GetRigidBody() const;

		CloudMath::Matrix4f GetTransform() const;
		CloudMath::Vector3f GetPosition() const;
		CloudMath::Quaternion GetRotation() const;
		void SetPosition(const CloudMath::Vector3f& p_vector3);
		void SetRotation(const CloudMath::Quaternion& p_quaternion);
		void SetTransform(const CloudMath::Matrix4f& p_transform);

		ACollider* GetCollider() const;
		void SetCollider(ACollider* p_collider);
		void SetMass(float p_mass);
		void SetFriction(float p_friction);
		void SetCollisionDetection(CollisionDetection p_collisionDetection);
		void Activate(bool p_activate);

		void AddForce(const CloudMath::Vector3f& p_vector3);

		CloudMath::Vector3f GetLinearVelocity() const;
		void SetLinearVelocity(const CloudMath::Vector3f& p_vector3) const;

		CloudMath::Vector3f GetAngularVelocity() const;
		void SetAngularVelocity(const CloudMath::Vector3f& p_vector3) const;

		/*
		 * Block movement or rotation on axis 0 to block 1 to free
		 */
		void SetConstraint(const CloudMath::Vector3f& p_linear, const CloudMath::Vector3f& p_angular);
		btTypedConstraint* GetConstraint() const;

		CloudMath::Vector3f GetLinearConstraint() const;
		CloudMath::Vector3f GetAngularConstraint() const;

		void SetIsTrigger(bool p_isTrigger);
		bool IsTrigger() const;

		void AddFlag(int p_flag);
		void RemoveFlag(int p_flag);
		void SetKinematic(bool p_isKinematic);
		bool IsKinematic() const;

	private:
		void ApplyConstraint();
		void SetFlags();
		void SetCollisionDetection();

		void CreateRigidBody();
		void DestroyRigidBody();

	public:
		// Events
		static Tools::Event<Physic::RigidBody&> creationEvent;
		static Tools::Event<Physic::RigidBody&> destructionEvent;

		Tools::Event<Physic::RigidBody*> onCollision{};
		Tools::Event<Physic::RigidBody*> onTrigger{};

		Tools::Event<Core::Collision&> onFillCollisionsInfo{};

	private:
		btRigidBody* m_rigidBody{nullptr};
		btMotionState* m_motion{nullptr};

		ACollider* m_collider{nullptr};

		btGeneric6DofConstraint* m_constraint;
		CloudMath::Vector3f m_linearConstraint;
		CloudMath::Vector3f m_angularConstraint;

		CollisionDetection m_collisionDetection;
		float m_mass;
		float m_friction;

		uint16_t m_onResizedShapeEvent;

		bool m_isTrigger;
		bool m_isKinematic;
	};
}
