#pragma once

#include <Core/stdafx.h>
#include <Core/CoreAPI.h>
#include <Core/ECS/System/System.h>
#include <Core/CoreComponent/MeshRenderer.h>
#include <Rendering/Renderer/Renderer.h>

/*
This is a big system responsible for rendering
for now it is basic but extensible to support our futur progress 
ex: support alpha by determining farther object to be renderer first
*/

namespace Core
{
	namespace Systems
	{
		using namespace Core;

		class CORE_API RenderingSystem : public System<RenderingSystem>
		{
		public:
			RenderingSystem(SystemPriority p_priority = SystemPriority::NORMAL_SYSTEM_PRIORITY,
				double p_updateInterval_ms = -1.0);

			~RenderingSystem();

			void Awake() override;
			void PostUpdate(double p_deltaTime) override;

		private:
			void OnReloadShader(Rendering::Shader* p_shader);

		private:
			/*std::shared_ptr<Rendering::Mesh> m_debugLightCubeMesh;*/
			std::shared_ptr<Rendering::Material> m_debugLightMaterial;
		};
	}
}