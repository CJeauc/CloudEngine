#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Entity/EntityManager.h"
#include "Core/ECS/Component/ComponentManager.h"
#include "Core/ECS/System/SystemManager.h"

namespace Core
{
	class CORE_API ECS
	{
		friend class CloudEngine;

	private:
		ECS();

	public:
		ECS(const ECS&) = delete;
		void operator=(const ECS&) = delete;

		static ECS& Get();

		void Clear();

		template <typename T, typename ...Args>
		std::shared_ptr<T> CreateEntity(Args&&... p_parameters)
		{
			return m_entityManager->CreateEntity<T>(std::forward<Args>(p_parameters)...);
		}

		template <typename T>
		const std::unordered_map<ComponentId, std::shared_ptr<Component<T>>>& GetComponents()
		{
			auto componentContainer = m_componentManager->GetComponentContainer<T>();

			return componentContainer->GetTypedComponentContainer();
		}

		std::shared_ptr<AEntity> GetOwner(std::shared_ptr<AComponent> p_component);

		std::shared_ptr<AEntity> GetEntity(EntityId p_entityId);

		template<typename T = Core::Entities::GameObject>
		std::shared_ptr<T> GetEntity(const std::string& p_name)
		{
			return m_entityManager->GetEntity<T>(p_name);
		}

		template <class T, class... Args>
		std::shared_ptr<T> AddSystem(Args&&... p_systemArgs)
		{
			return m_systemManager->AddSystem<T>(std::forward<Args>(p_systemArgs)...);
		}

		void Awake();

		template<class T>
		void SetSystemCore()
		{
			m_systemManager->SetAsCore<T>();
		}

	public:
		std::shared_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;

	private:
		std::unique_ptr<SystemManager> m_systemManager;
	};
}
