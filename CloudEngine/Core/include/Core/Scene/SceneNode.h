#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/CoreEntity/GameObject.h>

namespace Core
{
		using namespace Core::Entities;
		class Scene;

		class CORE_API SceneNode
		{
			friend class Scene;
		public:
			SceneNode(GameObject* p_gameObject);

			~SceneNode();
			void SetParent(SceneNode* p_parent);
			void AddChild(SceneNode* p_child);
			void AddChild(std::shared_ptr<SceneNode> p_child);
			void PopChild(SceneNode* p_child);
			void PopChild(std::shared_ptr<SceneNode> p_child);
			void RemoveChild(std::shared_ptr<SceneNode> p_child);
			void RemoveChild(SceneNode* p_child);
			void SetDirty(bool p_dirty);
			bool IsDirty() const;
			GameObject* GetGameObject();

			SceneNode* GetParent();
			SceneNode* GetChildAtIndex(unsigned int p_index);
			std::vector<SceneNode*>& GetChildren();

			unsigned int GetChildCount();
			int row();

		private:
			SceneNode();

		private:
			GameObject* m_gameObject;
			SceneNode* m_parent;
			std::vector<SceneNode*> m_children;
			uint16_t m_transformChangedEvent;
			bool m_dirty;				//Events to set dirty 
		};
}
