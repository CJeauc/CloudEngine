#include "Core/stdafx.h"
#include "Core/ECS/Entity/EntityManager.h"

Core::EntityManager::EntityManager(std::shared_ptr<ComponentManager> p_componentManager)
	: m_componentManager(std::move(p_componentManager)) {}

Core::EntityManager::~EntityManager()
{
}

void Core::EntityManager::DestroyEntity(const EntityId& p_entityId)
{
	const EntityTypeId entityTypeId = m_entityTable[p_entityId]->GetEntityTypeId();

	m_componentManager->RemoveAllComponents(p_entityId);

	m_entityRegistry[entityTypeId]->DestroyEntity(p_entityId);
	m_entityTable.erase(p_entityId);
}

Core::EntityManager::AEntity_ptr Core::EntityManager::GetEntity(const EntityId& p_entityId)
{
	try
	{
		return m_entityTable[p_entityId];
	}
	catch (std::out_of_range&)
	{
		LOG(Log::Error(), "The entity requested don't exist : " << p_entityId, Debug::LogStream::CONSOLE);
		return nullptr;
	}
}


