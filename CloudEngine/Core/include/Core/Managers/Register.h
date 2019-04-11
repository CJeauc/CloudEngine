#pragma once

#include "Core/CoreAPI.h"
#include "Core/stdafx.h"
#include "Tools.h"
#include "TypeFunctions.h"

namespace Core
{
	class CORE_API ARegistry
	{
		
	};

	/*
	 * Static class which associate type with Creators
	 */
	template <class T>
	class Registry : public ARegistry
	{
	public:
		using Creator = std::function<std::pair<unsigned int, std::string>(std::string, std::string)>;

	public:
		Registry() = default;

		/*
		 * Register a creator for a type
		 * @p_creator
		 */
		void Register(const Creator& p_creator)
		{
			if (!m_creator)
				m_creator = p_creator;
			else
				LOG(Log::Warning(), GetNameFromType<T>() << " already have a creator");
		}

		/*
		 * Call the Creator for the type
		 * @p_name		name of the resource to create
		 * @p_fileName	path to load with the creator
		 */
		std::shared_ptr<T> Create(std::string p_name, std::string p_fileName)
		{
			if (m_creator)
				return std::make_shared<T>(m_creator(p_name, p_fileName));

			LOG(Log::Warning(), GetNameFromType<T>() << " don't have any creator, Register one first");
			return nullptr;
		}

	private:
		Creator m_creator;
	};
}