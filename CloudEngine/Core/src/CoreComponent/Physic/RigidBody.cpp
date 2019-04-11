#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Core/CoreComponent/Physic/BoxCollider.h"
#include "Core/CoreComponent/Physic/SphereCollider.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "Core/ECS/ECS.h"
#include "Physic/Math/Conversion.h"

Core::Components::RigidBody::RigidBody(float p_mass)
	: m_physicObject(nullptr), m_mass(p_mass) {}

Core::Components::RigidBody::~RigidBody()
{
	m_physicObject->DisableRigidBody();
}

std::shared_ptr<Core::Components::PhysicObject> Core::Components::RigidBody::GetPhysicObject() const
{
	return m_physicObject;
}

float Core::Components::RigidBody::GetMass() const
{
	return m_mass;
}

void Core::Components::RigidBody::SetMass(float p_mass)
{
	m_mass = p_mass;
	m_physicObject->GetRigidBody()->SetMass(p_mass);
}

void Core::Components::RigidBody::AddForce(const CloudMath::Vector3f& p_vector3)
{
	m_physicObject->GetRigidBody()->AddForce(p_vector3);
}

CloudMath::Vector3f Core::Components::RigidBody::GetLinearVelocity() const
{
	return m_physicObject->GetRigidBody()->GetLinearVelocity();
}

void Core::Components::RigidBody::SetLinearVelocity(const CloudMath::Vector3f& p_vector3) const
{
	m_physicObject->GetRigidBody()->SetLinearVelocity(p_vector3);
}

CloudMath::Vector3f Core::Components::RigidBody::GetAngularVelocity() const
{
	return m_physicObject->GetRigidBody()->GetAngularVelocity();
}

void Core::Components::RigidBody::SetAngularVelocity(const CloudMath::Vector3f& p_vector3) const
{
	m_physicObject->GetRigidBody()->SetAngularVelocity(p_vector3);
}

void Core::Components::RigidBody::SetConstraint(const CloudMath::Vector3f& p_linear,
                                                const CloudMath::Vector3f& p_angular)
{
	m_physicObject->GetRigidBody()->SetConstraint(p_linear, p_angular);
}

bool Core::Components::RigidBody::IsGrounded(float p_accuracy) const
{
	return Cloud::Get().PhysicEngine()->RayCast(m_physicObject->GetTransform()->GetPosition(), {0.f, -1.f, 0.f},
	                                            m_physicObject->GetCollider()->GetScale().y *
	                                            m_physicObject->GetCollider()->GetVerticalDistanceFromCenter() +
	                                            p_accuracy);
}

void Core::Components::RigidBody::SetKinematic(bool p_isKinematic)
{
	m_physicObject->GetRigidBody()->SetKinematic(p_isKinematic);
}

void Core::Components::RigidBody::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	m_physicObject = owner->GetComponent<PhysicObject>();
	if (!m_physicObject)
		m_physicObject = owner->AddComponent<PhysicObject>(m_mass);
	else
		m_physicObject->CreateRigidBody(m_mass);
}
