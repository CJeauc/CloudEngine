#include "Core/stdafx.h"
#include "Core/CoreComponent/Physic/ACollider.h"

Core::Components::ACollider::~ACollider()
{
	m_physicObject->SetCollider(nullptr);
}

Physic::ACollider* Core::Components::ACollider::GetCollider() const
{
	return m_physicObject->GetCollider();
}

std::shared_ptr<Core::Components::PhysicObject> Core::Components::ACollider::GetPhysicObject() const
{
	return m_physicObject;
}

void Core::Components::ACollider::SetIsTrigger(bool p_isTrigger)
{
	m_physicObject->SetIsTrigger(p_isTrigger);
}

bool Core::Components::ACollider::IsTrigger() const
{
	return m_physicObject->IsTrigger();
}

Tools::Event<Core::Collision>& Core::Components::ACollider::OnCollisionEnter()
{
	return m_physicObject->m_collisionEvents.onCollisionEnter;
}

Tools::Event<Core::Collision>& Core::Components::ACollider::OnCollisionStay()
{
	return m_physicObject->m_collisionEvents.onCollisionStay;
}

Tools::Event<Core::Collision>& Core::Components::ACollider::OnCollisionExit()
{
	return m_physicObject->m_collisionEvents.onCollisionExit;
}

Tools::Event<std::shared_ptr<Core::Components::ACollider>>& Core::Components::ACollider::OnTriggerEnter()
{
	return m_physicObject->m_collisionEvents.onTriggerEnter;
}

Tools::Event<std::shared_ptr<Core::Components::ACollider>>& Core::Components::ACollider::OnTriggerStay()
{
	return m_physicObject->m_collisionEvents.onTriggerStay;
}

Tools::Event<std::shared_ptr<Core::Components::ACollider>>& Core::Components::ACollider::OnTriggerExit()
{
	return m_physicObject->m_collisionEvents.onTriggerExit;
}
