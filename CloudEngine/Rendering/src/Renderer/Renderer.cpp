#include "Rendering/stdafx.h"
#include "Rendering/Renderer/Renderer.h"
#include "CloudMath.h"

using namespace Rendering;

float Renderer::time = 0;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::InitDriver(GLADloadproc p_gladLoadProc)
{
	return (m_driver.Load(p_gladLoadProc));
}

bool Rendering::Renderer::InitGlad()
{
	if (!gladLoadGL())
		return false;

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//WireFrame
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	SLOG(Log::Info(), "Cloud Renderer initialized");

	return true;
}

void Renderer::Loop()
{
}

void Renderer::SetClearColor(const float p_r, const float p_g, const float p_b, const float p_alpha)
{
	glClearColor(p_r, p_g, p_b, p_alpha);
}

void Renderer::Render(Mesh& p_mesh, Material& p_material)
{
	p_material.Bind();
	p_mesh.Draw();
	p_material.UnBind();
}

void Renderer::Render(std::shared_ptr<Mesh> p_mesh, std::shared_ptr<Material> p_material)
{
	p_material->Bind();
	p_mesh->Draw();
	p_material->UnBind();
}

void Renderer::Render(Mesh* p_mesh, std::shared_ptr<Material> p_material)
{
	p_material->Bind();
	p_mesh->Draw();
	p_material->UnBind();
}

void Renderer::RenderSubModels(Model* p_model, std::shared_ptr<Material> p_material)
{
	if (p_model->HasSubMeshes())
	{
		for (unsigned int i = 0; i < p_model->Meshes().size(); ++i)
		{
			Texture* textureDiffuse = p_model->Materials()[i]->Slots()[0].second;
			p_material->SetTextureToSlot(p_material->GetTextureSlotByName("diffuseTex"), textureDiffuse);

			Texture* textureSpecular = p_model->Materials()[i]->Slots()[1].second;
			p_material->SetTextureToSlot(p_material->GetTextureSlotByName("specularTex"), textureSpecular);

			p_material->Bind();
			p_model->Meshes()[i]->Draw();
			p_material->UnBind();
		}
	}
}

void Renderer::DebugRender(DebugLight& p_light, Material& p_material)
{
	p_material.Bind();
	p_light.Draw();
	p_material.UnBind();
}

void Renderer::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame()
{
}
