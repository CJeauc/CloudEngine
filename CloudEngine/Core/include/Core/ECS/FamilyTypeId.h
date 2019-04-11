#pragma once

#include "any"
#include "Core/ECS/Types.h"
#include "Core/CoreAPI.h"

namespace Core::Components
{
	class Transform;
}
namespace Core::Entities
{
	class GameObject;
}

namespace Core
{
	class AFamilyTypeId
	{
	};

	template <typename T>
	class FamilyTypeId : public AFamilyTypeId
	{
	public:
		FamilyTypeId() = default;
		~FamilyTypeId()
		{
			for (auto& it : m_typeIds)
				delete it.second;
		}

		template <class U>
		TypeId* Get(std::string p_str)
		{
			// Magic line of the ECS
			// a unique type id is set for a pair of Type T and U
			// for a same T, a new U increments m_count
			// for a different T but a same U, the id will be different

			//static const TypeId typeId{ m_count++ };
			//return typeId;

			const auto it = m_typeIds.find(p_str);
			if (it == m_typeIds.end())
				return (m_typeIds[p_str] = new TypeId(m_count++));

			return it->second;
		}

		constexpr TypeId Get() const { return m_count; }

		std::unordered_map<std::string, TypeId*>& GetTypeIds() { return m_typeIds; }

	private:
		std::unordered_map<std::string, TypeId*> m_typeIds{};
		TypeId m_count;
	};

	template <typename T>
	class FamilyObjectId
	{
	public:
		FamilyObjectId() = default;
		~FamilyObjectId() = default;

		constexpr TypeId Get()
		{
			return m_count++;
		}

	private:
		TypeId m_count;
	};
}
