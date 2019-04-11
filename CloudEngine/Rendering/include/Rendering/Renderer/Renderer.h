#pragma once

#include "Rendering/stdafx.h"

#include "Rendering/RenderingAPI.h"
#include "Rendering/Driver/Driver.h"
#include "Rendering/Shading/ShaderLoader.h"
#include "Rendering/Shading/Textureloader.h"

#include "Rendering/Resource/Mesh.h"
#include "Rendering/Shading/Material.h"
#include "Rendering/Light/DebugLight.h"
#include <Rendering/Resource/Model.h>

namespace Rendering
{
	class RENDERING_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool InitDriver(GLADloadproc p_gladLoadProc);
		bool InitGlad();

		void Loop();
		void SetClearColor(const float p_r, const float p_g, const float p_b, const float p_alpha);
		static void Render(Mesh& p_mesh, Material& p_material);
		void DebugRender(DebugLight& p_light, Material& p_material);
		static void Render(std::shared_ptr<Mesh> p_mesh, std::shared_ptr<Material> p_material);
		static void Render(Mesh* p_mesh, std::shared_ptr<Material> p_material);
		static void RenderSubModels(Model* p_model, std::shared_ptr<Material> p_material);

		static float time;

		void BeginFrame();
		void EndFrame();

	private:
		Driver m_driver;
	};
}