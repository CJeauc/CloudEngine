#pragma once

#include "Core/CoreAPI.h"
#include "Core/ECS/Entity/Entity.h"
#include <Tools.h>

namespace Core
{
	namespace Entities
	{
		class CORE_API GameObject : public Entity<GameObject>
		{
		public:
			explicit GameObject(std::string p_name = { "GameObject" });
			GameObject(const GameObject& p_other);

			void Init() override;
			std::string Name();
			void SetName(const std::string& p_name);

			static Tools::Event<GameObject*> CreationEvent;

		private:
			std::string m_name;
		};
	}
}

