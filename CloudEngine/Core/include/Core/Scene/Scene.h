#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/Scene/SceneNode.h>
#include <Core/Serializer/TinyXML2.h>

using namespace TinyXML2;

namespace Core
{
	namespace Systems
	{
		class WorldTransformSystem;
	}

	class SceneManager;

	class CORE_API Scene
	{
		friend Systems::WorldTransformSystem;

	public:
		Scene(std::string p_name);
		~Scene();

		SceneNode* AddNode(GameObject* p_gameObject);
		SceneNode* AddNodeToParent(std::shared_ptr<GameObject> p_gameObject, SceneNode* p_parent);
		SceneNode* AddNodeToParent(std::shared_ptr<GameObject> p_gameObject, std::shared_ptr<GameObject> p_parent);

		void AddChild(SceneNode* p_child, SceneNode* p_parent);

		void Detach(std::shared_ptr<GameObject> p_node);
		std::string GetName();

		SceneNode* GetRoot();

		void Save();
		void SerializeNode(TinyXML2::XMLDocument& p_doc, Core::SceneNode* p_sceneNode, TinyXML2::XMLNode* p_parent);
		void SerializeComponents(TinyXML2::XMLDocument& p_doc, Core::SceneNode* p_sceneNode,
		                         TinyXML2::XMLNode* p_parent);

		void Load(std::string p_sceneName);
		void LoadGameObject(XMLElement* p_gameObjectNode, SceneNode* p_parent);
		void LoadComponent(std::shared_ptr<Core::Entities::GameObject> p_ownerGameObject, std::string p_componentType,
		                   XMLElement* p_componentNode);

	private:
		void LinkTransformWithNodes();
		std::unordered_map<GameObject*, SceneNode*> GetGameObjectNodeMap() const;

	private:
		std::unordered_map<GameObject*, SceneNode*> m_map;
		SceneNode* m_root;
		std::string m_name;
	};
}
