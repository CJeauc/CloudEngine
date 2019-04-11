#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/PhysicObject.h"
#include "Core/CoreComponent/Physic/ACollider.h"
#include "Core/CoreComponent/Transform.h"
#include "Core/ECS/ECS.h"
#include "Core/CoreEntity/GameObject.h"
#include "Core/CoreComponent/Physic/RigidBody.h"
#include "Core/CoreComponent/Physic/SphereCollider.h"
#include "Core/CoreComponent/Physic/BoxCollider.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "Physic/Collision/BoxCollider.h"
#include "Physic/Collision/CapsuleCollider.h"

using namespace Core::Components;
using namespace TinyXML2;

PhysicObject::PhysicObject()
	: m_collider(nullptr), m_rigidBody(nullptr), m_transform(nullptr), m_transformChangedEvent(0), m_mass(0) { }

PhysicObject::PhysicObject(float p_mass)
	: m_haveRigidBodyComponent(true), m_transformChangedEvent(0), m_mass(p_mass) {}

PhysicObject::PhysicObject(Physic::ACollider* p_collider)
	: m_collider(p_collider), m_haveColliderComponent(true), m_transformChangedEvent(0), m_mass(0) {}

PhysicObject::~PhysicObject()
{
	UnSubscribeToCollisionEvents();
	delete m_rigidBody;
	delete m_collider;
}

void PhysicObject::SetCollider(Physic::ACollider* p_collider)
{
	delete m_collider;
	m_collider = p_collider;

	m_haveColliderComponent = p_collider;

	SetupColliderAndRigidBody();
}

void PhysicObject::CreateRigidBody(float p_mass)
{
	m_mass = p_mass;
	m_haveRigidBodyComponent = true;

	if (!m_rigidBody)
	{
		m_rigidBody = new Physic::RigidBody(m_collider, m_transform->GetUnscaledTransform(), p_mass);
		SubscribeToCollisionEvents();
	}
	else
	{
		m_rigidBody->SetMass(p_mass);
		m_rigidBody->SetTransform(m_transform->GetUnscaledTransform());
	}
}

Physic::ACollider* PhysicObject::GetCollider() const
{
	return m_collider;
}

Physic::RigidBody* PhysicObject::GetRigidBody() const
{
	return m_rigidBody;
}

std::shared_ptr<Transform> PhysicObject::GetTransform() const
{
	return m_transform;
}

void PhysicObject::DisableRigidBody()
{
	m_haveRigidBodyComponent = false;
	m_rigidBody->Activate(false);
}

void PhysicObject::SetIsTrigger(bool p_isTrigger)
{
	m_rigidBody->SetIsTrigger(p_isTrigger);
}

bool PhysicObject::IsTrigger() const
{
	return m_rigidBody->IsTrigger();
}

void PhysicObject::Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const
{
	XMLElement* physicObject = p_doc.NewElement("Component");
	p_parent->InsertEndChild(physicObject);
	physicObject->SetAttribute("type", "PhysicObject");

	// RigidBody //
	XMLElement* rigidBody = p_doc.NewElement("RigidBody");
	physicObject->InsertEndChild(rigidBody);
	rigidBody->SetAttribute("haveRigidBodyComponent", m_haveRigidBodyComponent);
	rigidBody->SetAttribute("mass", m_mass);

	XMLElement* linearConstraint = p_doc.NewElement("LinearConstraint");
	rigidBody->InsertEndChild(linearConstraint);
	linearConstraint->SetAttribute("x", m_rigidBody->GetLinearConstraint().x);
	linearConstraint->SetAttribute("y", m_rigidBody->GetLinearConstraint().y);
	linearConstraint->SetAttribute("z", m_rigidBody->GetLinearConstraint().z);

	XMLElement* angularConstraint = p_doc.NewElement("AngularConstraint");
	rigidBody->InsertEndChild(angularConstraint);
	angularConstraint->SetAttribute("x", m_rigidBody->GetAngularConstraint().x);
	angularConstraint->SetAttribute("y", m_rigidBody->GetAngularConstraint().y);
	angularConstraint->SetAttribute("z", m_rigidBody->GetAngularConstraint().z);

	XMLElement* specification = p_doc.NewElement("Specification");
	rigidBody->InsertEndChild(specification);
	specification->SetAttribute("isTrigger", m_rigidBody->IsTrigger());
	specification->SetAttribute("isKinematic", m_rigidBody->IsKinematic());
	// ---------- //
	// Collider //
	const Physic::ACollider::ShapeType shapeType = m_collider->GetShapeType();

	XMLElement* collider = p_doc.NewElement("Collider");
	physicObject->InsertEndChild(collider);
	collider->SetAttribute("haveColliderComponent", m_haveColliderComponent);
	collider->SetAttribute("shapeType", static_cast<char>(shapeType));

	XMLElement* dimensions = p_doc.NewElement("Dimensions");
	collider->InsertEndChild(dimensions);

	switch (shapeType)
	{
	case Physic::ACollider::ShapeType::SPHERE:
		dimensions->SetAttribute("radius", dynamic_cast<Physic::SphereCollider*>(m_collider)->GetRadius());
		break;
	case Physic::ACollider::ShapeType::BOX:
		dimensions->SetAttribute("x", dynamic_cast<Physic::BoxCollider*>(m_collider)->GetBoxExtents().x);
		dimensions->SetAttribute("y", dynamic_cast<Physic::BoxCollider*>(m_collider)->GetBoxExtents().y);
		dimensions->SetAttribute("z", dynamic_cast<Physic::BoxCollider*>(m_collider)->GetBoxExtents().z);
		break;
	case Physic::ACollider::ShapeType::CAPSULE:
		dimensions->SetAttribute("radius", dynamic_cast<Physic::CapsuleCollider*>(m_collider)->GetRadius());
		dimensions->SetAttribute("height", dynamic_cast<Physic::CapsuleCollider*>(m_collider)->GetHeight());
		break;
	case Physic::ACollider::ShapeType::INVALID:
	default:
		break;
	}
	// ---------- //
}

void PhysicObject::DeSerialize(TinyXML2::XMLElement* p_componentNode)
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	TinyXML2::XMLElement* rigidBodyNode = p_componentNode->FirstChildElement("RigidBody");
	TinyXML2::XMLElement* colliderNode = p_componentNode->FirstChildElement("Collider");

	m_mass = std::strtof(rigidBodyNode->Attribute("mass"), nullptr);
	m_haveRigidBodyComponent = rigidBodyNode->Attribute("haveRigidBodyComponent")[0] == 't';
	m_haveColliderComponent = colliderNode->Attribute("haveColliderComponent")[0] == 't';

	// Collider //
	if (m_haveColliderComponent)
	{
		const char* oui = colliderNode->Attribute("shapeType");
		const Physic::ACollider::ShapeType shapeType = static_cast<Physic::ACollider::ShapeType>(
			static_cast<char>(std::strtof(oui, nullptr)));

		switch (shapeType)
		{
		case Physic::ACollider::ShapeType::SPHERE:
			owner->AddComponent<Components::SphereCollider>(
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("radius"), nullptr)
			);
			break;
		case Physic::ACollider::ShapeType::BOX:
			owner->AddComponent<Components::BoxCollider>(CloudMath::Vector3f{
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("x"), nullptr),
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("y"), nullptr),
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("z"), nullptr)
			});
			break;
		case Physic::ACollider::ShapeType::CAPSULE:
			owner->AddComponent<Components::CapsuleCollider>(
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("radius"), nullptr),
				std::strtof(colliderNode->FirstChildElement("Dimensions")->Attribute("height"), nullptr)
			);
			break;
		case Physic::ACollider::ShapeType::INVALID:
		default:
			break;
		}
		// ---------- //
	}

	if (m_haveRigidBodyComponent)
	{
		owner->AddComponent<Components::RigidBody>(m_mass);

		m_rigidBody->SetConstraint({
			                           std::strtof(rigidBodyNode->FirstChildElement("LinearConstraint")->Attribute("x"),
			                                       nullptr),
			                           std::strtof(rigidBodyNode->FirstChildElement("LinearConstraint")->Attribute("y"),
			                                       nullptr),
			                           std::strtof(rigidBodyNode->FirstChildElement("LinearConstraint")->Attribute("z"),
			                                       nullptr)
		                           },
		                           {
			                           std::strtof(
				                           rigidBodyNode->FirstChildElement("AngularConstraint")->Attribute("x"),
				                           nullptr),
			                           std::strtof(
				                           rigidBodyNode->FirstChildElement("AngularConstraint")->Attribute("y"),
				                           nullptr),
			                           std::strtof(
				                           rigidBodyNode->FirstChildElement("AngularConstraint")->Attribute("z"),
				                           nullptr)
		                           });

		m_rigidBody->SetIsTrigger(rigidBodyNode->FirstChildElement("Specification")->Attribute("isTrigger") == "true");
		m_rigidBody->
			SetKinematic(rigidBodyNode->FirstChildElement("Specification")->Attribute("isKinematic") == "true");
	}
}

void PhysicObject::Init()
{
	auto owner = ECS::Get().GetEntity(m_ownerId);

	m_transform = owner->AddComponent<Transform>();
	m_transformChangedEvent = m_transform->haveChangedEvent += BIND(&PhysicObject::OnTransformChangedEvent, this);

	if (m_haveRigidBodyComponent || m_haveColliderComponent)
		SetupColliderAndRigidBody();
}

void PhysicObject::RefreshRigidBodyData()
{
	m_rigidBody->SetTransform(m_transform->GetUnscaledTransform());
	m_collider->SetScale(m_transform->GetScale());
}

void PhysicObject::RefreshTransformData()
{
	if (m_haveRigidBodyComponent)
	{
		m_transform->SetPosition(m_rigidBody->GetPosition());
		m_transform->SetRotation(m_rigidBody->GetRotation());
	}
}

void PhysicObject::RefreshCollisionStates()
{
	for (auto it = m_collisionEvents.collisionState.begin(); it != m_collisionEvents.collisionState.end();)
	{
		if (!it->second.first)
		{
			Collision collision;
			it->second.second->onFillCollisionsInfo.Invoke(collision);
			m_collisionEvents.onCollisionExit.Invoke(collision);
			it = m_collisionEvents.collisionState.erase(it);
		}
		else
		{
			it->second.first = false;
			++it;
		}
	}

	for (auto it = m_collisionEvents.triggerState.begin(); it != m_collisionEvents.triggerState.end();)
	{
		if (!it->second.first)
		{
			Collision collision;
			it->second.second->onFillCollisionsInfo.Invoke(collision);
			m_collisionEvents.onTriggerExit.Invoke(collision.collider);
			it = m_collisionEvents.triggerState.erase(it);
		}
		else
		{
			it->second.first = false;
			++it;
		}
	}
}

void PhysicObject::OnTransformChangedEvent()
{
	m_rigidBody->Activate(true);
}

void PhysicObject::SetupColliderAndRigidBody()
{
	const bool noCollider = !m_collider;
	if (noCollider)
		m_collider = new Physic::SphereCollider();

	if (!m_rigidBody)
	{
		m_rigidBody = new Physic::RigidBody(m_collider, m_transform->GetUnscaledTransform(), m_mass);
		SubscribeToCollisionEvents();
	}
	else
		m_rigidBody->SetCollider(m_collider);

	if (noCollider)
		m_rigidBody->AddFlag(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	else
		m_rigidBody->AddFlag(btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}

void PhysicObject::SubscribeToCollisionEvents()
{
	m_collisionEvents.onCollision =
		m_rigidBody->onCollision += BIND(&Core::Components::PhysicObject::OnCollision, this, HOLDER_1);

	m_collisionEvents.onTrigger =
		m_rigidBody->onTrigger += BIND(&Core::Components::PhysicObject::OnTrigger, this, HOLDER_1);

	m_collisionEvents.onFillCollisionsInfo +=
		m_rigidBody->onFillCollisionsInfo += BIND(&Core::Components::PhysicObject::OnFillCollisionsInfo, this, HOLDER_1
		);
}

void PhysicObject::UnSubscribeToCollisionEvents()
{
	m_rigidBody->onCollision -= m_collisionEvents.onCollision;
	m_rigidBody->onTrigger -= m_collisionEvents.onTrigger;
	m_rigidBody->onFillCollisionsInfo -= m_collisionEvents.onFillCollisionsInfo;
}

void PhysicObject::OnCollision(Physic::RigidBody* p_otherRigidBody)
{
	auto owner = std::static_pointer_cast<Entities::GameObject>(ECS::Get().GetEntity(m_ownerId));

	Collision collision{};
	p_otherRigidBody->onFillCollisionsInfo.Invoke(collision);

	auto collisionState = m_collisionEvents.collisionState.find(collision.gameObject->Name());
	if (collisionState != m_collisionEvents.collisionState.end())
	{
		collisionState->second.first = true;
		m_collisionEvents.onCollisionStay.Invoke(collision);
	}
	else
	{
		m_collisionEvents.collisionState[collision.gameObject->Name()] = {true, p_otherRigidBody};
		m_collisionEvents.onCollisionEnter.Invoke(collision);
	}
}

void PhysicObject::OnTrigger(Physic::RigidBody* p_otherRigidBody)
{
	auto owner = std::static_pointer_cast<Entities::GameObject>(ECS::Get().GetEntity(m_ownerId));

	Collision collision{};
	p_otherRigidBody->onFillCollisionsInfo.Invoke(collision);

	auto collisionState = m_collisionEvents.triggerState.find(collision.gameObject->Name());
	if (collisionState != m_collisionEvents.triggerState.end())
	{
		collisionState->second.first = true;
		m_collisionEvents.onTriggerStay.Invoke(collision.collider);
	}
	else
	{
		m_collisionEvents.triggerState[collision.gameObject->Name()] = {true, p_otherRigidBody};
		m_collisionEvents.onTriggerEnter.Invoke(collision.collider);
	}
}

void PhysicObject::OnFillCollisionsInfo(Core::Collision& p_collisionInfo)
{
	auto owner = ECS::Get().GetEntity(m_ownerId);
	p_collisionInfo.gameObject = std::static_pointer_cast<Entities::GameObject>(owner);

	p_collisionInfo.collider = owner->GetComponent<Components::SphereCollider>();
	if (!p_collisionInfo.collider)
	{
		p_collisionInfo.collider = owner->GetComponent<Components::BoxCollider>();
		if (!p_collisionInfo.collider)
			p_collisionInfo.collider = owner->GetComponent<Components::CapsuleCollider>();
	}

	p_collisionInfo.rigidBody = owner->GetComponent<Components::RigidBody>();
	p_collisionInfo.transform = m_transform;
}
