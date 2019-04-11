#pragma once

#include "Core/CoreAPI.h"
#include "Core/stdafx.h"
#include "Tools.h"

#include "ASystem.h"

#include "memory"

namespace Core
{
	class CloudEngine;
	class ECS;

	class CORE_API SystemManager
	{
		using ASystem_ptr = std::shared_ptr<ASystem>;

		friend class Core::CloudEngine;
		friend class Core::ECS;

	public:
		SystemManager() = default;
		~SystemManager();

		template <class T, class... Args>
		std::shared_ptr<T> AddSystem(Args&&... p_systemArgs)
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end() && iterator->second != nullptr)
			{
				LOG(Log::Warning(), "The system " << systemTypeId << " already exist", Debug::
					LogStream::FILE);
				return std::static_pointer_cast<T>(iterator->second);
			}

			std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<Args>(p_systemArgs)...);
			newSystem->m_systemManager = this;

			auto resultCreation = m_systemRegistry.try_emplace(systemTypeId, newSystem);
			ASSERTD(resultCreation.second, "Error creating new System");

			// resize dependency matrix
			if (systemTypeId + 1 > m_systemDependencyMatrix.size())
			{
				m_systemDependencyMatrix.resize(systemTypeId + 1);
				for (int i = 0; i < this->m_systemDependencyMatrix.size(); ++i)
					m_systemDependencyMatrix[i].resize(systemTypeId + 1);
			}

			m_systemWorkOrder.push_back(newSystem);

			return newSystem;
		}

		template <class System_, class Dependency_>
		void AddSystemDependency(System_ p_targetSystem, Dependency_ p_dependency)
		{
			const TypeId targetSystemId = p_targetSystem->StaticSystemTypeId;
			const TypeId dependencyId = p_dependency->StaticSystemTypeId;

			try
			{
				m_systemDependencyMatrix.at(targetSystemId).at(dependencyId) = true;
			}
			catch (std::out_of_range&)
			{
				LOG(Log::Error(), "One of the systems isn't registered yet", Debug::LogStream::FILE);
			}
		}

		template <class System_, class Dependency_, class... Dependencies>
		void AddSystemDependency(System_ p_targetSystem, Dependency_ p_dependency, Dependencies&&... p_dependencies)
		{
			const TypeId targetSystemId = p_targetSystem->StaticSystemTypeId;
			const TypeId dependencyId = p_dependency->StaticSystemTypeId;

			try
			{
				m_systemDependencyMatrix[targetSystemId][dependencyId] = true;
				this->AddSystemDependency(p_targetSystem, std::forward<Dependencies>(p_dependencies)...);
			}
			catch (std::out_of_range&)
			{
				LOG(Log::Error(), p_targetSystem->GetSystemTypeName() <<
					" or one of the dependencies isn't registered yet", Debug::LogStream::FILE);
			}
		}

		void UpdateSystemWorkOrder();

		template <class T>
		std::shared_ptr<T> GetSystem() const
		{
			try
			{
				return std::static_pointer_cast<T>(m_systemRegistry.at(T::StaticSystemTypeId));
			}
			catch (std::out_of_range)
			{
				LOG(Log::Error(), "The System requested doesn't exist : " << T::StaticSystemTypeId, Debug::LogStream::
					FILE);
				return nullptr;
			}
		}

		template <class T>
		void EnableSystem()
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end())
				iterator->second->m_enabled = true;
			else
				LOG(Log::Warning(), "System " << systemTypeId << " can't be enable, system is not registered yet", Debug::LogStream::FILE);
		}

		template <class T>
		void DisableSystem()
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end())
				iterator->second->m_enabled = false;
			else
				LOG(Log::Warning(), "System " << systemTypeId << " can't be disable, system is not registered yet", Debug::LogStream::FILE);
		}

		template <class T>
		void SetSystemUpdateInterval(double p_interval_ms)
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end())
				iterator->second->m_updateInterval = p_interval_ms;
			else
				LOG(Log::Warning(), "System " << systemTypeId <<
				"'s updateInterval can't be change, system is not registered yet", Debug::LogStream::FILE);
		}

		template <class T>
		void SetSystemPriority(SystemPriority p_newPriority)
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			// get system
			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end())
				iterator->second->m_priority = p_newPriority;
			else
				LOG(Log::Warning(), "System " << systemTypeId <<
				"'s priority can't be change, system is not registered yet", Debug::LogStream::FILE);
		}

		void Clear();

	private:
		void Awake();
		void FixedUpdate(double p_fixedDeltaTime);
		void PreUpdate(double p_deltaTime);
		void Update(double p_deltaTime);
		void PostUpdate(double p_deltaTime);

		template <class T>
		void SetAsCore()
		{
			const SystemTypeId systemTypeId = T::StaticSystemTypeId;

			// get system
			const auto iterator = m_systemRegistry.find(systemTypeId);
			if (iterator != m_systemRegistry.end())
				iterator->second->m_isCore = true;
			else
				LOG(Log::Warning(), "System " << systemTypeId <<
					"'s can't be set as core, system is not registered yet", Debug::LogStream::FILE);
		}

	private:
		using SystemGroupsPriority = std::multimap<SystemPriority, std::vector<SystemTypeId>>;

		/*
		 * Regroup system depending on there dependencies and there SystemPriority, vectors send must be empty
		 * @param p_systemGroups	vector to be fill with group of system depending on there dependencies
		 * @param p_groupsPriority	vector to be fill with system priority for each groups
		 */
		void CreateSystemsGroupsWithPriority(std::vector<std::vector<SystemTypeId>>& p_systemGroups,
		                                     std::vector<SystemPriority>& p_groupsPriority) const;

		SystemGroupsPriority SortGroupsByPriority(const std::vector<std::vector<SystemTypeId>>& p_systemGroups,
		                                          const std::vector<SystemPriority>& p_groupsPriority) const;

	private:
		std::unordered_map<SystemTypeId, ASystem_ptr> m_systemRegistry;
		std::vector<std::vector<bool>> m_systemDependencyMatrix;
		std::vector<ASystem_ptr> m_systemWorkOrder;

		double m_timeSinceFixedUpdate {0.0};
		double m_timeBetweenFixedUpdate {0.02};
	};
}
