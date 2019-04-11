#pragma once

#include "Core/ECS/Types.h"
#include "Core/CoreAPI.h"
#include <Core/Serializer/TinyXML2.h>

namespace Core
{
	class CORE_API AComponent
	{
		friend class ComponentManager;

	protected:
		AComponent();

		virtual void Init() {}

	public:
		virtual ~AComponent() = default;

		inline bool operator==(const AComponent& p_other) const { return m_componentId == p_other.m_componentId; }
		inline bool operator!=(const AComponent& p_other) const { return m_componentId != p_other.m_componentId; }
		inline bool operator==(const AComponent* p_other) const { return m_componentId == p_other->m_componentId; }
		inline bool operator!=(const AComponent* p_other) const { return m_componentId != p_other->m_componentId; }

		const ComponentId& GetComponentId() const;
		const EntityId& GetOwnerId() const;

		virtual ComponentTypeId GetComponentTypeId() const = 0;
		virtual void Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const = 0;
		virtual void DeSerialize(TinyXML2::XMLElement* p_componentNode) = 0;

		void SetActive(const bool p_active);
		bool IsActive() const;

	protected:
		EntityId m_ownerId;
		ComponentId m_componentId;
		bool m_active;
	};
}
