#pragma once

#include "Core/ECS/Component/ComponentManager.h"
#include "Entity.h"
#include "Tools.h"

namespace Core
{
	class CORE_API EntityManager
	{
	private:
		using AEntity_ptr = std::shared_ptr<AEntity>;

		/*--- EntityContainer ---*/

		class IEntityContainer
		{
		public:
			virtual ~IEntityContainer() = default;
			virtual void DestroyEntity(const EntityId& p_object) = 0;
		};

		template <typename T>
		class EntityContainer : public IEntityContainer
		{
			using TypedEntityContainer = std::unordered_map<EntityId, std::shared_ptr<Entity<T>>>;

			EntityContainer(const EntityContainer&) = delete;
			EntityContainer& operator=(EntityContainer&) = delete;

		public:
			EntityContainer() {}

			~EntityContainer() override { }

			void DestroyEntity(const EntityId& p_object) override
			{
				m_typedContainer.erase(p_object);
			}

			TypedEntityContainer& GetTypedEntityContainer() { return m_typedContainer; }

		private:
			TypedEntityContainer m_typedContainer;
		};

		/*-----------------------*/

	public:
		explicit EntityManager(std::shared_ptr<ComponentManager> p_componentManager);
		~EntityManager();

		template <typename T, typename ...Args>
		std::shared_ptr<T> CreateEntity(Args&&... p_parameters)
		{
			EntityId newId = m_componentManager->m_entityFamilyObjectId.Get();

			std::shared_ptr<T> newEntity = std::make_shared<T>(std::forward<Args>(p_parameters)...);

			newEntity->m_entityId = newId;
			newEntity->m_componentManagerInstance = m_componentManager;

			newEntity->Init();

			auto resultCreation = m_entityTable.try_emplace(newId, newEntity);
			ASSERTD(resultCreation.second, "Error creating new entity");

			auto resultInsertion = GetEntityContainer<T>()->GetTypedEntityContainer().try_emplace(newId, newEntity);
			ASSERTD(resultInsertion.second, "Error inserting entity in typed containers");

			return newEntity;
		}

		void DestroyEntity(const EntityId& p_entityId);

		AEntity_ptr GetEntity(const EntityId& p_entityId);

		template<typename T>
		std::shared_ptr<T> GetEntity(const std::string& p_name)
		{
			try
			{
				auto typedEntityMap = GetEntityContainer<T>()->GetTypedEntityContainer();

				for (auto it : typedEntityMap)
				{
					auto entity = std::static_pointer_cast<T>(it.second);
					if (entity->Name() == p_name)
						return entity;
				}
				return nullptr;
			}
			catch(std::out_of_range e)
			{
				return nullptr;
			}
		}

		template <typename ToKeep, typename ToDestroy>
		void Clear()
		{
			EntityTypeId daemonTypeId = ToKeep::StaticEntityTypeId;

			for (auto typedEntityContainerIterator : GetEntityContainer<ToDestroy>()->GetTypedEntityContainer())
			{
				m_componentManager->RemoveAllComponents(typedEntityContainerIterator.first);
				m_entityTable.erase(typedEntityContainerIterator.first);
			}

			auto it = m_entityRegistry.begin();
			auto toDestroy = it;
			while (it != m_entityRegistry.end())
			{
				if (it->first != daemonTypeId)
				{
					toDestroy = it;
					++it;
					m_entityRegistry.erase(toDestroy->first);
				}
				else
					++it;
			}
		}

	private:
		template <typename T>
		EntityContainer<T>* GetEntityContainer()
		{
			EntityTypeId entityTypeId = T::StaticEntityTypeId;

			const auto iterator = m_entityRegistry.find(entityTypeId);
			if (iterator != m_entityRegistry.end())
				return reinterpret_cast<EntityContainer<T>*>(iterator->second.get());

			const auto resultCreation = m_entityRegistry.try_emplace(entityTypeId,
			                                                         std::make_unique<EntityContainer<T>>());
			ASSERTD(resultCreation.second, "Failed to create EntityContainer<T>");
			return reinterpret_cast<EntityContainer<T>*>(resultCreation.first->second.get());
		}

	private:
		using AEntityContainer_ptr = std::shared_ptr<IEntityContainer>;

		std::unordered_map<EntityTypeId, AEntityContainer_ptr> m_entityRegistry;
		std::unordered_map<EntityId, AEntity_ptr> m_entityTable;
		std::shared_ptr<ComponentManager> m_componentManager;
	};
}
