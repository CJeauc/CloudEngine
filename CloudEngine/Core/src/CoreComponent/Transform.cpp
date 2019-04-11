#include "Core/stdafx.h"
#include "Core/CoreComponent/Transform.h"

using namespace Core::Components;
using namespace TinyXML2;

Transform::Transform(const CloudMath::Vector3f& p_position,
                     const CloudMath::Vector3f& p_rotationXYZ,
                     const CloudMath::Vector3f& p_scale)
	: m_position(p_position), m_rotation(p_rotationXYZ.z, p_rotationXYZ.y, p_rotationXYZ.z),
	  m_scale(p_scale), m_isUpdate(false)
{
	CalculateTransform();
}

CloudMath::Matrix4f Transform::GetTransform()
{
	CalculateTransform();
	return m_parentTransform ? m_parentTransform->GetTransform() * m_localTransform : m_localTransform;
}

CloudMath::Matrix4f Transform::GetTransform() const
{
	return m_parentTransform ? m_parentTransform->GetTransform() * m_localTransform : m_localTransform;
}

CloudMath::Matrix4f Transform::GetUnscaledTransform() const
{
	return m_parentTransform ? m_parentTransform->GetUnscaledTransform() * CloudMath::Matrix4f::Translation(m_position) * m_rotation.ToMatrix4() : CloudMath::Matrix4f::Translation(m_position) * m_rotation.ToMatrix4();
}

CloudMath::Vector3f Transform::GetPosition() const
{
	return m_position;
}

CloudMath::Quaternion Transform::GetRotation() const
{
	return m_rotation;
}

CloudMath::Vector3f Transform::GetScale() const
{
	return m_scale;
}

CloudMath::Vector3f Core::Components::Transform::GetFront() const
{
	return m_rotation.RotateVector({ 0, 0, 1 });
}

CloudMath::Vector3f Core::Components::Transform::GetUp() const
{
	return m_rotation.RotateVector({ 0, 1, 0 });
}

CloudMath::Vector3f Core::Components::Transform::GetRight() const
{
	return m_rotation.RotateVector({ -1, 0, 0 });
}

CloudMath::Vector3f Transform::GetWorldPosition() const
{
	return m_parentTransform ? m_parentTransform->GetWorldPosition() + m_position : m_position;
}

CloudMath::Quaternion Transform::GetWorldRotation() const
{
	return m_parentTransform ? m_parentTransform->GetWorldRotation() * m_rotation : m_rotation;
}

CloudMath::Vector3f Transform::GetWorldScale() const
{
	return m_parentTransform ? m_parentTransform->GetWorldScale() + m_scale : m_scale;
}

CloudMath::Vector3f Transform::GetWorldFront() const
{
	return m_parentTransform ? (m_parentTransform->GetWorldRotation() * m_rotation).RotateVector({0, 0, 1}) : m_rotation.RotateVector({ 0, 0, 1 });
}

CloudMath::Vector3f Transform::GetWorldUp() const
{
	return m_parentTransform ? (m_parentTransform->GetWorldRotation() * m_rotation).RotateVector({ 0, 1, 0 }) : m_rotation.RotateVector({ 0, 1, 0 });
}

CloudMath::Vector3f Transform::GetWorldRight() const
{
	return m_parentTransform ? (m_parentTransform->GetWorldRotation() * m_rotation).RotateVector({ -1, 0, 0 }) : m_rotation.RotateVector({ -1, 0, 0 });
}

bool Transform::IsUpdate() const
{
	return m_isUpdate;
}

void Transform::SetParentTransform(std::shared_ptr<Transform> p_parentTransform)
{
	m_parentTransform = p_parentTransform;
}

/* --------------- */

void Transform::SetPosition(const CloudMath::Vector3f& p_position)
{
	if (m_position != p_position)
	{
		m_position = p_position;
		m_isUpdate = false;
	}
}

void Transform::SetRotation(const CloudMath::Vector3f& p_rotationXYZ)
{
	m_rotation = CloudMath::Quaternion(p_rotationXYZ.z, p_rotationXYZ.y, p_rotationXYZ.x);
	m_isUpdate = false;
}

void Transform::SetRotation(const CloudMath::Quaternion& p_rotation)
{
	if (m_rotation != p_rotation)
	{
		m_rotation = p_rotation;
		m_rotation.Normalize();

		m_isUpdate = false;
	}
}

void Transform::SetScale(const CloudMath::Vector3f& p_scale)
{
	if (m_scale != p_scale)
	{
		m_scale = p_scale;
		m_isUpdate = false;
	}
}

void Transform::Rotate(const CloudMath::Vector3f& p_vector3)
{
	m_rotation *= CloudMath::Quaternion(p_vector3);
	m_rotation.Normalize();
	m_isUpdate = false;
}

void Transform::Rotate(const CloudMath::Quaternion& p_quaternion)
{
	m_rotation *= p_quaternion;
	m_rotation.Normalize();
	m_isUpdate = false;
}

void Transform::Translate(const CloudMath::Vector3f& p_translation)
{
	m_position += p_translation;
	m_isUpdate = false;
}

void Transform::ForceUpdateState(const bool p_newUpdateState)
{
	m_isUpdate = p_newUpdateState;
}

void Transform::Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const
{
	XMLElement* transform = p_doc.NewElement("Component");
	p_parent->InsertEndChild(transform);
	transform->SetAttribute("type", "Transform");

	XMLElement* position = p_doc.NewElement("Position");
	transform->InsertEndChild(position);
	position->SetAttribute("x", m_position.x);
	position->SetAttribute("y", m_position.y);
	position->SetAttribute("z", m_position.z);

	XMLElement* rotation = p_doc.NewElement("Rotation");
	transform->InsertEndChild(rotation);
	rotation->SetAttribute("x", m_rotation.GetXAxisValue());
	rotation->SetAttribute("y", m_rotation.GetYAxisValue());
	rotation->SetAttribute("z", m_rotation.GetZAxisValue());
	rotation->SetAttribute("w", m_rotation.GetRealValue());

	XMLElement* scale = p_doc.NewElement("Scale");
	transform->InsertEndChild(scale);
	scale->SetAttribute("x", m_scale.x);
	scale->SetAttribute("y", m_scale.y);
	scale->SetAttribute("z", m_scale.z);
}

void Transform::DeSerialize(TinyXML2::XMLElement* p_componentNode)
{
	//Position
	m_position.x = std::strtof(p_componentNode->FirstChildElement("Position")->Attribute("x"), nullptr);
	m_position.y = std::strtof(p_componentNode->FirstChildElement("Position")->Attribute("y"), nullptr);
	m_position.z = std::strtof(p_componentNode->FirstChildElement("Position")->Attribute("z"), nullptr);

	//Rotation
	m_rotation.SetXAxisValue(std::strtof(p_componentNode->FirstChildElement("Rotation")->Attribute("x"), nullptr));
	m_rotation.SetYAxisValue(std::strtof(p_componentNode->FirstChildElement("Rotation")->Attribute("y"), nullptr));
	m_rotation.SetZAxisValue(std::strtof(p_componentNode->FirstChildElement("Rotation")->Attribute("z"), nullptr));
	m_rotation.SetRealValue(std::strtof(p_componentNode->FirstChildElement("Rotation")->Attribute("w"), nullptr));

	//Scale
	m_scale.x = std::strtof(p_componentNode->FirstChildElement("Scale")->Attribute("x"), nullptr);
	m_scale.y = std::strtof(p_componentNode->FirstChildElement("Scale")->Attribute("y"), nullptr);
	m_scale.z = std::strtof(p_componentNode->FirstChildElement("Scale")->Attribute("z"), nullptr);

	m_isUpdate = false;
}

/* --------------- */

void Transform::CalculateTransform()
{
	if (!m_isUpdate)
	{
		m_localTransform = CloudMath::Matrix4f::Translation(m_position) *
			m_rotation.ToMatrix4() *
			CloudMath::Matrix4f::Scaling(m_scale);

		haveChangedEvent.Invoke();
		m_isUpdate = true;
	}
}
