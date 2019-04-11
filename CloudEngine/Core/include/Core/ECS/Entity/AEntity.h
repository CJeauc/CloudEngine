#pragma once

#include "Core/ECS/Types.h"
#include "Core/CoreAPI.h"
#include "Core/ECS/Component/ComponentManager.h"

namespace Core
{
		class CORE_API AEntity
		{
			friend class EntityManager;

		protected:
			virtual void Init() {}

		public:
			explicit AEntity();
			virtual ~AEntity() = default;

			template<typename T, typename ...Param>
			std::shared_ptr<T> AddComponent(Param&&... p_parameters)
			{
				return m_componentManagerInstance->AddComponent<T>(m_entityId, std::forward<Param>(p_parameters)...);
			}

			template<typename T>
			std::shared_ptr<T> GetComponent()
			{
				return m_componentManagerInstance->GetComponent<T>(m_entityId);
			}

			template<typename T>
			void RemoveComponent()
			{
				m_componentManagerInstance->RemoveComponent<T>(m_entityId);
			}

			inline bool operator==(const AEntity& p_other) const { return m_entityId == p_other.m_entityId; }
			inline bool operator!=(const AEntity& p_other) const { return m_entityId != p_other.m_entityId; }
			inline bool operator==(const AEntity* p_other) const { return m_entityId == p_other->m_entityId; }
			inline bool operator!=(const AEntity* p_other) const { return m_entityId != p_other->m_entityId; }

			virtual EntityTypeId GetEntityTypeId() const = 0;

			inline EntityId GetEntityId() const { return m_entityId; }

			void SetActive(bool p_active);

			std::vector<std::shared_ptr<AComponent>> GetComponents();

			inline bool IsActive() const { return m_active; }

		protected:
			virtual void OnEnable() { 
				(Debug::Log::Info(), "Enable", Debug::LogStream::CONSOLE); }
			virtual void OnDisable() { LOG(Log::Info(), "Disable", Debug::LogStream::CONSOLE); }

		protected:
			EntityId m_entityId;
			bool m_active;

		private:
			std::shared_ptr<ComponentManager> m_componentManagerInstance;
		};
}
