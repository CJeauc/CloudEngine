#pragma once

#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/UniformRendering.h>
#include <Rendering/Resource/Cube.h>

/*
The engine will always create a uniform rendering entity
this entity will have the uniform rendering component

this system will create the buffers in the awake

this system will be responsible of updating this data
*/

namespace Core
{
	namespace Systems
	{
		using namespace Core;

		class CORE_API UniformRenderingSystem : public Core::System<UniformRenderingSystem>
		{
		public:
			UniformRenderingSystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			void Awake() override;
			void Update(double p_deltaTime) override;
		};
	}
}