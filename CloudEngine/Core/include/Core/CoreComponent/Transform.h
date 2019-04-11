#pragma once

#include <CloudMath.h>
#include "Core/CoreAPI.h"
#include "Core/ECS/Component/Component.h"
#include "Tools/Event/Event.h"

/*
  Ze Transform. No explenation needed
*/

namespace Core
{
	namespace Components
	{
		class CORE_API Transform : public Component<Transform>
		{
		public:
			explicit Transform(const CloudMath::Vector3f& p_position = {0, 0, 0},
			                   const CloudMath::Vector3f& p_rotationXYZ = {0, 0, 0},
			                   const CloudMath::Vector3f& p_scale = {1, 1, 1});

			/*
			* Update and return the transformation matrix
			*/
			CloudMath::Matrix4f GetTransform();

			/*
			 * Get the transformation matrix but don't update it
			 * if position rotation or scale have change
			 */
			CloudMath::Matrix4f GetTransform() const;

			/*
			* Get the transformation matrix without scale
			*/
			CloudMath::Matrix4f GetUnscaledTransform() const;

			CloudMath::Vector3f GetPosition() const;
			CloudMath::Quaternion GetRotation() const;
			CloudMath::Vector3f GetScale() const;
			CloudMath::Vector3f GetFront() const;
			CloudMath::Vector3f GetUp() const;
			CloudMath::Vector3f GetRight() const;

			CloudMath::Vector3f GetWorldPosition() const;
			CloudMath::Quaternion GetWorldRotation() const;
			CloudMath::Vector3f GetWorldScale() const;
			CloudMath::Vector3f GetWorldFront() const;
			CloudMath::Vector3f GetWorldUp() const;
			CloudMath::Vector3f GetWorldRight() const;

			bool IsUpdate() const;

			void SetParentTransform(std::shared_ptr<Transform> p_parentTransform);

			void SetPosition(const CloudMath::Vector3f& p_position);
			void SetRotation(const CloudMath::Vector3f& p_rotationXYZ);
			void SetRotation(const CloudMath::Quaternion& p_rotation);
			void SetScale(const CloudMath::Vector3f& p_scale);

			void Rotate(const CloudMath::Vector3f& p_vector3);
			void Rotate(const CloudMath::Quaternion& p_quaternion);
			void Translate(const CloudMath::Vector3f& p_translation);

			void ForceUpdateState(bool p_newUpdateState = false);
			void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const override;
			void DeSerialize(TinyXML2::XMLElement* p_componentNode) override;

			Tools::Event<> haveChangedEvent;

		private:
			void CalculateTransform();

		private:
			std::shared_ptr<Transform> m_parentTransform {};
			CloudMath::Matrix4f m_localTransform;

			CloudMath::Vector3f m_position;
			CloudMath::Quaternion m_rotation;
			CloudMath::Vector3f m_scale;

			bool m_isUpdate;
		};
	}
}
