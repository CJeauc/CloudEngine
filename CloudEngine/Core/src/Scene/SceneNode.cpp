#include <Core/stdafx.h>
#include <Core/Scene/SceneNode.h>
#include "Core/CoreComponent/Transform.h"

using namespace Core;

SceneNode::SceneNode()
	: m_gameObject {nullptr}, m_parent {nullptr}, m_transformChangedEvent(0), m_dirty(false) {}

SceneNode::SceneNode(GameObject* p_gameObject)
	: m_gameObject {p_gameObject}, m_parent {nullptr}, m_transformChangedEvent(0), m_dirty {true} {}

SceneNode::~SceneNode()
{
	m_children.clear();
}

void SceneNode::SetParent(SceneNode* p_parent)
{
	m_parent = p_parent;
	if (m_gameObject)
	{
		auto transform = m_gameObject->GetComponent<Components::Transform>();
		if (transform)
			transform->SetParentTransform(p_parent->GetGameObject()->GetComponent<Components::Transform>());
	}
}

void SceneNode::AddChild(SceneNode* p_child)
{
	m_children.emplace_back(p_child);
	if (m_gameObject)
	{
		auto transform = p_child->GetGameObject()->GetComponent<Components::Transform>();
		if (transform)
			transform->SetParentTransform(m_gameObject->GetComponent<Components::Transform>());
	}
}

void SceneNode::AddChild(std::shared_ptr<SceneNode> p_child)
{
	m_children.push_back(p_child.get());
	if (m_gameObject)
	{
		auto transform = p_child->GetGameObject()->GetComponent<Components::Transform>();
		if (transform)
			transform->SetParentTransform(m_gameObject->GetComponent<Components::Transform>());
	}
}

void SceneNode::PopChild(SceneNode* p_child)
{
	auto it = std::find_if(m_children.begin(), m_children.end(), [&](SceneNode* p_node)
	{
		if (p_node->GetGameObject() == p_child->GetGameObject())
			return true;
		else return false;
	});
	if (it != m_children.end())
	{
		std::swap(*it, m_children.back());

		auto transform = m_children.back()->GetGameObject()->GetComponent<Components::Transform>();
		if (transform)
			transform->SetParentTransform(nullptr);

		m_children.pop_back();
	}
}

void Core::SceneNode::RemoveChild(std::shared_ptr<SceneNode> p_child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), p_child.get()));

	auto transform = p_child->GetGameObject()->GetComponent<Components::Transform>();
	if (transform)
			transform->SetParentTransform(nullptr);
}

void SceneNode::RemoveChild(SceneNode* p_child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), p_child));
	auto transform = p_child->GetGameObject()->GetComponent<Components::Transform>();
	if (transform)
		transform->SetParentTransform(nullptr);
}

void SceneNode::PopChild(std::shared_ptr<SceneNode> p_child)
{
	auto it = std::find_if(m_children.begin(), m_children.end(), [&](SceneNode* p_node)
	{
		if (p_node->GetGameObject() == p_child->GetGameObject()) return true;
		else return false;
	});
	if (it != m_children.end())
	{
		std::swap(*it, m_children.back());

		auto transform = m_children.back()->GetGameObject()->GetComponent<Components::Transform>();
		if (transform)
			transform->SetParentTransform(nullptr);
		m_children.pop_back();
	}
}

void SceneNode::SetDirty(bool p_dirty)
{
	m_dirty = p_dirty;

	if (p_dirty)
		for (auto child : m_children)
			child->SetDirty(p_dirty);
}

bool SceneNode::IsDirty() const
{
	return m_dirty;
}

GameObject* Core::SceneNode::GetGameObject()
{
	return m_gameObject;
}

SceneNode* SceneNode::GetParent()
{
	return m_parent;
}

SceneNode* SceneNode::GetChildAtIndex(unsigned int p_index)
{
	unsigned int counter = 0;

	if (p_index > m_children.size())
	{
		return nullptr;
	}

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		if (counter == p_index)
			return *it;
		++counter;
	}

	return nullptr;
}

std::vector<SceneNode*>& SceneNode::GetChildren()
{
	return m_children;
}

unsigned int SceneNode::GetChildCount()
{
	return static_cast<unsigned int>(m_children.size());
}

int SceneNode::row()
{
	if (m_parent)
	{
		for (unsigned int i = 0; i < m_parent->GetChildCount(); ++i)
		{
			if (m_parent->GetChildAtIndex(i) == this)
			{
				return i;
			}
		}
	}
	return 0;
}
