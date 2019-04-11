#include "Core/stdafx.h"
#include "Core/ECS/System/ASystem.h"

Core::ASystem::ASystem(SystemPriority p_priority, double p_updateInterval_s)
	: m_timeSinceLastUpdate{ 0 }, m_priority{ p_priority }, m_updateInterval{ p_updateInterval_s },
	  m_enabled{true}, m_needsUpdate{true}, m_reserved{0} { }

