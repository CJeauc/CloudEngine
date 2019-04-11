#pragma once

#include "Core/CoreAPI.h"
#include "Core/stdafx.h"
#include "Register.h"
#include "TypeFunctions.h"
#include "Core/Engine/Cloud.h"
#include <Rendering/Resource/Mesh.h>

namespace Core
{
	/*
	 * Class used for resources of type T creation and access
	 */
	template <typename T>
	class ResourceManager : public AResourceManager
	{
		static_assert(!std::is_pointer<T>::value, "ResourceManager doesnt support pointers");
		static_assert(std::is_class<T>::value, "ResourceManager only support class types");

	public:
		ResourceManager()
		{
			m_resourceFolderPath = "../Resources/" + GetNameFromType<T>() + '/';
		}

		~ResourceManager() {}

		//static ResourceManager<T>& Get()
		//{
		//	static ResourceManager<T> instance;
		//	return instance;
		//}

		void SetResourceFolderPath(std::string p_path)
		{
			m_resourceFolderPath = std::move(p_path);
		}

		/*
		 * Load a resource, a creator have to be register for the type, use REGISTER_RES(type, creator)
		 * @p_name		name of the resource to create
		 * @p_fileName	path of the resource to load
		 */
		size_t Load(std::string p_name, std::string p_fileName)
		{
			const size_t resourceID = std::hash<std::string>()(p_name);
			 if (m_resources.find(resourceID) != m_resources.end())
				 *m_resources[resourceID] = std::move(*Cloud::Get().Registry<T>()->Create(p_name, m_resourceFolderPath + p_fileName));
			 else
				m_resources[resourceID] = Cloud::Get().Registry<T>()->Create(p_name, m_resourceFolderPath + p_fileName);

			return resourceID;
		}

		/*
		 * Get the resource
		 * @p_resourceName name of the resource given on the load of the resource
		 */
		std::shared_ptr<T> GetResource(std::string p_resourceName) const
		{
			const size_t resourceID = std::hash<std::string>()(p_resourceName);
			auto it = m_resources.find(resourceID);
			if (it != m_resources.end())
				return it->second;

			return nullptr;
		}

		/*
		 * Get the resource 
		 * @p_resourceID ID of the resource given on the load of the resource
		 */
		std::shared_ptr<T> GetResource(size_t p_resourceId) const
		{
			auto it = m_resources.find(p_resourceId);
			if (it != m_resources.end())
				return it->second;

			return nullptr;
		}

		/*
		 * Get the path of the resources folder
		 */
		std::string GetPath() const
		{
			return m_resourceFolderPath;
		}


	private:
		// std::string m_resourceFolderPath;
		std::unordered_map<size_t, std::shared_ptr<T>> m_resources;
	};
}
