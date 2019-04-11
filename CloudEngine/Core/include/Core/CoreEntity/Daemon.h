#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Entity/Entity.h>

namespace Core
{
	namespace Entities
	{
		class CORE_API Daemon : public Entity<Daemon>
		{
		public:
			explicit Daemon(std::string p_name = {"Daemon"});

		private:
			std::string m_name;
		};
	}
}