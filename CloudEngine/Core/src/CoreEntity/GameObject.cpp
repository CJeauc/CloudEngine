#include "Core/stdafx.h"
#include "Core/CoreEntity/GameObject.h"

using namespace Core::Entities;

Tools::Event<GameObject*> GameObject::CreationEvent;

GameObject::GameObject(std::string p_name)
	: m_name(std::move(p_name)) {}

GameObject::GameObject(const GameObject& p_other)
	: m_name(p_other.m_name) {}

std::string GameObject::Name()
{
	return m_name;
}

void GameObject::SetName(const std::string& p_name)
{
	m_name = p_name;
}

void GameObject::Init()
{
	CreationEvent.Invoke(this);
}
