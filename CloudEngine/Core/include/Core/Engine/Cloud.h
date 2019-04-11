#pragma once
#include "Core/ECS/FamilyTypeId.h"
#include "Physic/Simulation/PhysicEngine.h"
#include "Core/Managers/Register.h"

/*
* Use this macro to register a creator for a type
*/
#define REGISTER_RES(type, creator) (Cloud::Get().Registry<type>()->Register(creator))

namespace Core
{
	class CORE_API AResourceManager
	{
	protected:
		std::string m_resourceFolderPath;
	};

	template<typename T>
	class ResourceManager;
}

class CORE_API Cloud
{
private:
	Cloud();
	~Cloud();

public:
	static Cloud& Get();

	template<typename T>
	Core::FamilyTypeId<T>* FamilyType()
	{
		const auto it = m_familyTypeIds.find(typeid(T).name());
		if (it == m_familyTypeIds.end())
			return static_cast<Core::FamilyTypeId<T>*>(m_familyTypeIds[typeid(T).name()] = new Core::FamilyTypeId<T>);

		return static_cast<Core::FamilyTypeId<T>*>(it->second);
	}

	::PhysicEngine* PhysicEngine() const;

	template<typename T>
	Core::ResourceManager<T>* ResourceManager()
	{
		const auto it = m_resourceManagers.find(typeid(T).name());
		if (it == m_resourceManagers.end())
			return static_cast<Core::ResourceManager<T>*>(m_resourceManagers[typeid(T).name()] = new Core::ResourceManager<T>);

		return static_cast<Core::ResourceManager<T>*>(it->second);
	}

	template<typename T>
	Core::Registry<T>* Registry()
	{
		const auto it = m_register.find(typeid(T).name());
		if (it == m_register.end())
			return static_cast<Core::Registry<T>*>(m_register[typeid(T).name()] = new Core::Registry<T>);

		return static_cast<Core::Registry<T>*>(it->second);
	}

private:
	std::unordered_map<std::string, Core::AFamilyTypeId*> m_familyTypeIds;
	::PhysicEngine* m_physicEngine;
	std::unordered_map<std::string, Core::AResourceManager*> m_resourceManagers;
	std::unordered_map<std::string, Core::ARegistry*> m_register;
};
