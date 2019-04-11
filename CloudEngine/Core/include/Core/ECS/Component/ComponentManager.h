#pragma once

#include "Component.h"
#include "Tools.h"

namespace Core
{
	class AEntity;

	class CORE_API ComponentManager
	{
		friend class ECS;

	private:
		using AComponent_ptr = std::shared_ptr<AComponent>;

		class IComponentContainer
		{
		public:

			virtual ~IComponentContainer() = default;

			virtual std::string GetComponentContainerTypeName() const = 0;

			virtual void DestroyComponent(const ComponentId& p_object) = 0;
		};

		template <typename T>
		class ComponentContainer : public IComponentContainer
		{
			using TypedComponentContainer = std::unordered_map<ComponentId, std::shared_ptr<Component<T>>>;

		public:
			ComponentContainer() {}

			std::string GetComponentContainerTypeName() const override
			{
				static std::string typeName{typeid(T).name()};
				return typeName;
			}

			void DestroyComponent(const ComponentId& p_object) override
			{
				m_typedContainer.erase(p_object);
			}

			TypedComponentContainer& GetTypedComponentContainer() { return m_typedContainer; }

		private:
			TypedComponentContainer m_typedContainer;
		};

	public:
		ComponentManager() = default;
		~ComponentManager();

		template <typename T, typename ...Args>
		std::shared_ptr<T> AddComponent(const EntityId& p_entityId, Args&&... p_parameters)
		{
			const ComponentId newId = m_componentFamilyObjectId.Get();
			const ComponentTypeId componentTypeId = T::StaticComponentTypeId;
			
			auto& componentTable = m_entityComponentTable[p_entityId];
			if (componentTable.find(componentTypeId) != componentTable.end())
			{
				LOG(Log::Warning(), "The entity " << p_entityId << " already have component of type " << typeid(T).
					name(), Debug::LogStream::FILE);
				return std::static_pointer_cast<T>(m_componentTable.at(componentTable[componentTypeId]));
			}
			
			componentTable[componentTypeId] = newId;
			
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<Args>(p_parameters)...);
			newComponent->m_ownerId = p_entityId;
			newComponent->m_componentId = newId;
			
			auto resultCreation = m_componentTable.try_emplace(newId, newComponent);
			ASSERTD(resultCreation.second, "Error creating new Component");
			
			resultCreation.first->second->Init();
			
			auto resultInsertion = GetComponentContainer<T>()
			                       ->GetTypedComponentContainer().try_emplace(newId, newComponent);
			ASSERTD(resultInsertion.second, "Error inserting component in typed containers");
			
			return newComponent;
		}

		template <typename T>
		void RemoveComponent(const EntityId& p_entityId)
		{
			const ComponentTypeId componentTypeId = T::StaticComponentTypeId;

			try
			{
				const ComponentId componentId = m_entityComponentTable.at(p_entityId).at(componentTypeId);

				m_componentRegistry[componentTypeId]->DestroyComponent(componentId);
				m_componentTable.erase(componentId);
				m_entityComponentTable.at(p_entityId).erase(componentTypeId);
			}
			catch (std::out_of_range)
			{
				LOG(Log::Error(), "The entity " << p_entityId << " doesn't have component of type " << typeid(T).
					name(), Debug::LogStream::FILE)
			}
		}

		void RemoveAllComponents(const EntityId p_entityId);

		template <typename T>
		std::shared_ptr<T> GetComponent(const EntityId p_entityId)
		{
			const ComponentTypeId componentTypeId = T::StaticComponentTypeId;
			try
			{
				const ComponentId componentId = this->m_entityComponentTable.at(p_entityId).at(componentTypeId);
				return std::static_pointer_cast<T>(m_componentTable.at(componentId));
			}
			catch (std::out_of_range)
			{
				LOG(Log::Error(), "The entity requested doesn't exist : " << p_entityId, Debug::LogStream::FILE);
				return nullptr;
			}
		}

		std::vector<AComponent_ptr> GetComponentsOfEntity(const EntityId p_entityId) const
		{
			std::vector<AComponent_ptr> components;

			try 
			{
				auto componentsMap = m_entityComponentTable.at(p_entityId);

				for (auto it : componentsMap)
				{
					components.emplace_back(m_componentTable.at(it.second));
				}
			}
			catch (std::out_of_range)
			{
				LOG(Log::Error(), "The entity requested doesn't exist : " << p_entityId, Debug::LogStream::FILE);
			}

			return components;
		}
		
	private:
		template <typename T>
		ComponentContainer<T>* GetComponentContainer()
		{
			ComponentTypeId componentTypeId = T::StaticComponentTypeId;

			const auto iterator = m_componentRegistry.find(componentTypeId);
			if (iterator != m_componentRegistry.end())
				return reinterpret_cast<ComponentContainer<T>*>(iterator->second.get());

			auto resultCreation = m_componentRegistry.try_emplace(componentTypeId,
			                                                      std::make_unique<ComponentContainer<T>>());
			ASSERTD(resultCreation.second, "Failed to create ComponentContainer<T>");

			return reinterpret_cast<ComponentContainer<T>*>(resultCreation.first->second.get());
		}

	private:
		using AComponentContainer_ptr = std::shared_ptr<IComponentContainer>;

		std::unordered_map<ComponentTypeId, AComponentContainer_ptr> m_componentRegistry;
		std::unordered_map<ComponentId, AComponent_ptr> m_componentTable;
		std::unordered_map<EntityId, std::unordered_map<ComponentTypeId, ComponentId>> m_entityComponentTable;

	public:
		FamilyObjectId<AComponent> m_componentFamilyObjectId;
		FamilyObjectId<AEntity> m_entityFamilyObjectId;
	};
}
