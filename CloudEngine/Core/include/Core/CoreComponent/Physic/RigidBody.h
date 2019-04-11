#pragma once

#include "Core/CoreAPI.h"
#include "Core/CoreComponent/Transform.h"
#include "Core/CoreComponent/Physic/PhysicObject.h"
#include "Physic/Dynamics/RigidBody.h"

namespace Core
{
	namespace Components
	{
		class CORE_API RigidBody : public Component<RigidBody>
		{
		public:
			explicit RigidBody(float p_mass = 1);
			~RigidBody();

			std::shared_ptr<PhysicObject> GetPhysicObject() const;

			float GetMass() const;
			void SetMass(float p_mass);

			void AddForce(const CloudMath::Vector3f& p_vector3);

			CloudMath::Vector3f GetLinearVelocity() const;
			void SetLinearVelocity(const CloudMath::Vector3f& p_vector3) const;

			CloudMath::Vector3f GetAngularVelocity() const;
			void SetAngularVelocity(const CloudMath::Vector3f& p_vector3) const;

			/*
			* Block movement or rotation on axis 0 to block, 1 to free
			*/
			void SetConstraint(const CloudMath::Vector3f& p_linear, const CloudMath::Vector3f& p_angular);

			bool IsGrounded(float p_accuracy = 0.01f) const;

			void SetKinematic(bool p_isKinematic);

		protected:
			void Init() override;

		private:
			std::shared_ptr<PhysicObject> m_physicObject;
			float m_mass;
		};
	}
}
