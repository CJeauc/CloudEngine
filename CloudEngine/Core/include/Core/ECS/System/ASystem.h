#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Types.h"
#include "SystemPriorityDefine.h"

namespace Core
{
	class CORE_API ASystem
	{
		friend class SystemManager;

	protected:
		explicit ASystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
		                 double p_updateInterval_s = -1.0);

	public:
		virtual ~ASystem() = default;

		virtual inline SystemTypeId GetSystemTypeId() const = 0;

		virtual void Awake() = 0;
		virtual void FixedUpdate(double p_fixedDeltaTime) = 0;
		virtual void PreUpdate(double p_deltaTime) = 0;
		virtual void Update(double p_deltaTime) = 0;
		virtual void PostUpdate(double p_deltaTime) = 0;

	private:
		// Duration since last system update in milliseconds.
		double m_timeSinceLastUpdate;

		SystemPriority m_priority;

		// A negative value means system should update each time the engine receives an update.
		double m_updateInterval;

		uint8_t m_enabled : 1;
		uint8_t m_needsUpdate : 1;
		uint8_t m_reserved : 6;

		bool m_isCore = false;
	};
}
