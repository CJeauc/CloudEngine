#include "Core/stdafx.h"
#include "Core/ECS/Component/ComponentManager.h"
#include "Core/ECS/Component/AComponent.h"

Core::ComponentManager::~ComponentManager()
{
	
}

void Core::ComponentManager::RemoveAllComponents(const EntityId p_entityId)
{
	if (m_entityComponentTable.find(p_entityId) != m_entityComponentTable.end())
	{
		auto& components = m_entityComponentTable.at(p_entityId);
		for (auto iterator = components.begin(); iterator != components.end();)
		{
			m_componentRegistry.at(iterator->first)->DestroyComponent(iterator->second);
			m_componentTable.erase(iterator->second);

			// go to the next element
			iterator = components.erase(iterator);
		}
	}
}

