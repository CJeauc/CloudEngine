#include <Core/stdafx.h>
#include <Core/Scene/Scene.h>
#include <Core/ECS/ECS.h>
#include <Core/CoreComponent/Transform.h>
#include <Core/Engine/Cloud.h>
#include <Core/Managers/ResourceManager.h>
#include <Core/CoreComponent/MeshRenderer.h>
#include <Core/CoreComponent/MaterialRenderer.h>
#include <Core/CoreComponent/Physic/PhysicObject.h>
#include <Rendering.h>
#include "Rendering/Resource/Cube.h"

using namespace Core;

Scene::Scene(std::string p_name)
	: m_name {p_name}
{
	m_root = new SceneNode();
	m_map[nullptr] = m_root;
}

Scene::~Scene()
{
	for(auto it : m_map)
	{
		delete it.second;
	}
}


SceneNode* Scene::AddNode(GameObject* p_gameObject)
{
	auto node = new SceneNode(p_gameObject);

	m_root->AddChild(node);
	node->SetParent(m_root);
	m_map[p_gameObject] = node;
	return node;
}

SceneNode* Scene::AddNodeToParent(std::shared_ptr<GameObject> p_gameObject, SceneNode* p_parent)
{
	auto node = AddNode(p_gameObject.get());

	p_parent->AddChild(node);

	node->SetParent(p_parent);

	return node;
}


SceneNode* Scene::AddNodeToParent(std::shared_ptr<GameObject> p_child, std::shared_ptr<GameObject> p_parent)
{
	auto parent = m_map.find(p_parent.get());

	auto child = m_map.find(p_child.get());

	if (parent != m_map.end() && child != m_map.end())
	{
		parent->second->AddChild(child->second);
		child->second->GetParent()->RemoveChild(child->second);
		child->second->SetParent(parent->second);
		return parent->second;
	}

	return nullptr;
}

void Core::Scene::AddChild(SceneNode* p_child, SceneNode* p_parent)
{
	p_parent->AddChild(p_child);
	p_child->SetParent(p_parent);
}

void Scene::Detach(std::shared_ptr<GameObject> p_node)
{
	auto child = m_map.find(p_node.get());

	if (child != m_map.end())
	{
		m_root->AddChild(child->second);
		child->second->GetParent()->RemoveChild(child->second);
		child->second->SetParent(m_root);
	}
}

std::string Scene::GetName()
{
	return m_name;
}

SceneNode* Core::Scene::GetRoot()
{
	return m_root;
}

void Core::Scene::Save()
{
	XMLDocument sceneXML;

	XMLNode* root = sceneXML.NewElement("CloudEngine");

	sceneXML.InsertFirstChild(root);

	XMLElement* sceneRoot = sceneXML.NewElement("Scene");
	root->InsertEndChild(sceneRoot);

	sceneRoot->SetAttribute("name", m_name.c_str());

	for (auto child : m_root->GetChildren())
	{
		SerializeNode(sceneXML, child, sceneRoot);
	}

	std::string sceneName;
	sceneName = "../Resources/Scenes/";
	sceneName += m_name;
	sceneName += ".cloud";

	sceneXML.SaveFile(sceneName.c_str());
}

void Scene::SerializeNode(TinyXML2::XMLDocument& p_doc, Core::SceneNode* p_sceneNode, TinyXML2::XMLNode* p_parent)
{
	XMLElement* gameObject = p_doc.NewElement("GameObject");
	p_parent->InsertEndChild(gameObject);

	gameObject->SetAttribute("name", p_sceneNode->GetGameObject()->Name().c_str());

	SerializeComponents(p_doc, p_sceneNode, gameObject);

	if (p_sceneNode->GetChildCount() > 0)
		for (auto child : p_sceneNode->GetChildren())
			SerializeNode(p_doc, child, gameObject);
}

void Core::Scene::SerializeComponents(TinyXML2::XMLDocument & p_doc, Core::SceneNode* p_sceneNode, TinyXML2::XMLNode * p_parent)
{
	if (ECS::Get().m_componentManager->GetComponentsOfEntity(p_sceneNode->GetGameObject()->GetEntityId()).size() > 0)
	{
		XMLElement* gameObjectComponents = p_doc.NewElement("Components");
		p_parent->InsertEndChild(gameObjectComponents);

		for (auto component : ECS::Get().m_componentManager->GetComponentsOfEntity(p_sceneNode->GetGameObject()->GetEntityId()))
		{
			component->Serialize(p_doc, gameObjectComponents);
		}
	}
}

void Scene::Load(std::string p_sceneName)
{
	std::string path;
	path = "../Resources/Scenes/";
	path += p_sceneName;
	path += ".cloud";

	XMLDocument sceneXML;
	XMLError result;
	result = sceneXML.LoadFile(path.c_str());

	if (result != XML_SUCCESS)
	{
		SLOG(Log::Warning(), "UnableTo Open Scene. Please Check your Path");
		return;
	}

	XMLNode* root = sceneXML.FirstChild();

	/*Retreive Scene Tag for Scene Name Attribute*/
	XMLElement* sceneTag = root->FirstChildElement("Scene");
	const char* sceneName = nullptr;
	m_name = sceneTag->Attribute("name");

	XMLElement* gameObjectNode = sceneTag->FirstChildElement("GameObject");
	while (gameObjectNode != nullptr)
	{
		LoadGameObject(gameObjectNode, m_root);
		gameObjectNode = gameObjectNode->NextSiblingElement("GameObject");
	}
}

void Scene::LoadGameObject(XMLElement* p_gameObjectNode, SceneNode* p_parent)
{
	std::string gameObjectName;
	gameObjectName = p_gameObjectNode->Attribute("name");

	//Care GameObjects Get added to the active Scene
	auto gameObject = ECS::Get().m_entityManager->CreateEntity<Core::Entities::GameObject>(gameObjectName);

	auto gameObjectSceneNode = m_map.find(gameObject.get())->second;

	if (p_parent != m_root)
		p_parent->AddChild(gameObjectSceneNode);
	
	gameObjectSceneNode->SetParent(p_parent);

	if(gameObjectSceneNode->GetParent() != m_root)
		m_root->PopChild(gameObjectSceneNode);

	XMLElement* components = p_gameObjectNode->FirstChildElement("Components");

	if (components)
	{
		XMLElement* componentNode = components->FirstChildElement("Component");

		while (componentNode != nullptr)
		{
			std::string componentName;
			componentName = componentNode->Attribute("type");
			LoadComponent(gameObject, componentName, componentNode);
			componentNode = componentNode->NextSiblingElement("Component");
		}
	}

	XMLElement* childGameObject = p_gameObjectNode->FirstChildElement("GameObject");

	if(childGameObject)
	{
		while (childGameObject)
		{
			LoadGameObject(childGameObject, gameObjectSceneNode);
			childGameObject = childGameObject->NextSiblingElement("GameObject");
		}
	}
}

void Scene::LoadComponent(std::shared_ptr<Core::Entities::GameObject> p_ownerGameObject, std::string p_componentType, XMLElement* p_componentNode)
{
	if (p_componentType == "Transform")
	{
		auto transform = p_ownerGameObject->AddComponent<Core::Components::Transform>();

		transform->DeSerialize(p_componentNode);
	}

	if (p_componentType == "MaterialRenderer")
	{
		std::string shaderName = p_componentNode->FirstChildElement("Shader")->Attribute("name");

		auto shader = Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource(shaderName);

		auto material = std::make_shared<Rendering::Material>(shader.get());

		material->SetShader(shader.get());

		auto materialRenderer = p_ownerGameObject->AddComponent<Core::Components::MaterialRenderer>(material);
		materialRenderer->DeSerialize(p_componentNode);
	}

	if (p_componentType == "MeshRenderer")
	{
		auto meshRenderer = p_ownerGameObject->AddComponent<Core::Components::MeshRenderer>();
		meshRenderer->DeSerialize(p_componentNode);
	}

	if (p_componentType == "PhysicObject")
	{
		auto physicObject = p_ownerGameObject->AddComponent<Core::Components::PhysicObject>();
		physicObject->DeSerialize(p_componentNode);
	}
}

void Scene::LinkTransformWithNodes()
{
	for (auto it : m_map)
	{
		if (it.first)
		{
			auto transform = it.first->GetComponent<Components::Transform>();
			if (transform)
				it.second->m_transformChangedEvent = transform->haveChangedEvent += BIND(&Core::SceneNode::SetDirty, it.second, true);
		}
	}
}

std::unordered_map<GameObject*, SceneNode*> Scene::GetGameObjectNodeMap() const
{
	return m_map;
}
