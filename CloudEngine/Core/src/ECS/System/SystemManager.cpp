#include "Core/stdafx.h"
#include "Core/ECS/System/SystemManager.h"
#include "Core/ECS/Utils/Algorithm.h"
#include "Core/ECS/System/SystemPriorityDefine.h"
#include "Core/ECS/FamilyTypeId.h"

using namespace Core;

SystemManager::~SystemManager()
{
	m_systemWorkOrder.clear();
	m_systemRegistry.clear();
}

void SystemManager::UpdateSystemWorkOrder()
{
	// determine vertex-groups
	std::vector<std::vector<SystemTypeId>> systemsGroups;
	std::vector<SystemPriority> groupsPriority;

	CreateSystemsGroupsWithPriority(systemsGroups, groupsPriority);

	SystemGroupsPriority sortedVertexGroups = SortGroupsByPriority(systemsGroups, groupsPriority);

	// re-build system work order
	m_systemWorkOrder.clear();
	for (auto group : sortedVertexGroups)
	{
		for (SystemTypeId systemTypeId : group.second)
		{
			const ASystem_ptr sys = this->m_systemRegistry[systemTypeId];
			if (sys != nullptr)
			{
				this->m_systemWorkOrder.push_back(sys);
			}
		}
	}
}

void SystemManager::Clear()
{
	auto it = m_systemRegistry.begin();
	auto toDestroy = it;
	while (it != m_systemRegistry.end())
	{
		if (!it->second->m_isCore)
		{
			toDestroy = it;
			++it;
			m_systemRegistry.erase(toDestroy->first);
		}
		else
			++it;
	}
	
	UpdateSystemWorkOrder();
}

void SystemManager::Awake()
{
	UpdateSystemWorkOrder();

	for (ASystem_ptr system : m_systemWorkOrder)
	{
		if (system->m_enabled)
		{
			system->Awake();
		}
	}
}

void SystemManager::FixedUpdate(double p_fixedDeltaTime)
{
	// increase interval since last update
	m_timeSinceFixedUpdate += p_fixedDeltaTime;

	while (m_timeSinceFixedUpdate >= m_timeBetweenFixedUpdate)
	{
		for (ASystem_ptr system : m_systemWorkOrder)
		{
			if (system->m_enabled)
				system->FixedUpdate(m_timeBetweenFixedUpdate);
		}
		m_timeSinceFixedUpdate -= m_timeBetweenFixedUpdate;
	}
}

void SystemManager::PreUpdate(double p_deltaTime)
{
	for (ASystem_ptr system : m_systemWorkOrder)
	{
		// increase interval since last update
		system->m_timeSinceLastUpdate += p_deltaTime;

		// check systems update state
		system->m_needsUpdate = (system->m_updateInterval < 0.) ||
			(system->m_updateInterval > 0. && system->m_timeSinceLastUpdate > system->m_updateInterval);

		if (system->m_enabled && system->m_needsUpdate)
			system->PreUpdate(p_deltaTime);
	}
}

void SystemManager::Update(double p_deltaTime)
{
	for (ASystem_ptr system : this->m_systemWorkOrder)
	{
		if (system->m_enabled && system->m_needsUpdate)
		{
			system->Update(p_deltaTime);
			system->m_timeSinceLastUpdate = 0.;
		}
	}
}

void SystemManager::PostUpdate(double p_deltaTime)
{
	for (ASystem_ptr system : this->m_systemWorkOrder)
	{
		if (system->m_enabled == true && system->m_needsUpdate == true)
		{
			system->PostUpdate(p_deltaTime);
		}
	}
}

void SystemManager::CreateSystemsGroupsWithPriority(std::vector<std::vector<SystemTypeId>>& p_systemGroups,
                                                    std::vector<Core::SystemPriority>& p_groupsPriority) const
{
	const size_t systemsCount = m_systemDependencyMatrix.size();

	// create index array
	std::vector<int32_t> indices(systemsCount);
	for (int32_t i = 0; i < systemsCount; ++i)
	{
		indices[i] = i;
	}

	while (!indices.empty())
	{
		int32_t index = indices.back();
		indices.pop_back();

		if (index == -1)
			continue;

		std::vector<SystemTypeId> group;
		std::vector<int32_t> member;
		member.push_back(index);

		SystemPriority currentGroupPriority = SystemPriority::LOWEST_SYSTEM_PRIORITY;

		while (!member.empty())
		{
			index = member.back();
			member.pop_back();

			for (int32_t i = 0; i < indices.size(); ++i)
			{
				if (indices[i] != -1 &&
					(m_systemDependencyMatrix[i][index] == true || m_systemDependencyMatrix[index][i] == true))
				{
					member.push_back(i);
					indices[i] = -1;
				}
			}

			ASystem_ptr sys = nullptr;
			auto it = m_systemRegistry.find(index);
			if (it != m_systemRegistry.end())
			{
				group.push_back(index);
				sys = it->second;
			}

			currentGroupPriority = std::max((sys != nullptr ? sys->m_priority : SystemPriority::NORMAL_SYSTEM_PRIORITY),
			                                currentGroupPriority);
		}

		p_systemGroups.push_back(group);
		p_groupsPriority.push_back(currentGroupPriority);
	}
}

SystemManager::SystemGroupsPriority SystemManager::SortGroupsByPriority(
	const std::vector<std::vector<SystemTypeId>>& p_systemGroups,
	const std::vector<Core::SystemPriority>& p_groupsPriority) const
{
	// used with DepthFirstSearch to store visited nodes
	std::vector<int> vertexStates(m_systemDependencyMatrix.size(), 0);

	std::multimap<SystemPriority, std::vector<SystemTypeId>> sortedSystemsGroups;

	for (size_t i = 0; i < p_systemGroups.size(); ++i)
	{
		std::vector<SystemTypeId> group = p_systemGroups[i];
		std::vector<SystemTypeId> order;

		for (size_t j = 0; j < group.size(); ++j)
		{
			if (vertexStates[group[j]] == 0)
				Utils::DepthFirstSearch<SystemTypeId>(group[j], vertexStates, m_systemDependencyMatrix, order);
		}

		std::reverse(order.begin(), order.end());

		sortedSystemsGroups.insert(
			std::pair<SystemPriority, std::vector<SystemTypeId>>(
				std::numeric_limits<SystemPriority>::max() - p_groupsPriority[i], order));
	}

	return sortedSystemsGroups;
}
