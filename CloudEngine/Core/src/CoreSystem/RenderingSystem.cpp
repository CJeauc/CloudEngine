#include <Core/stdafx.h>
#include <Core/CoreSystem/RenderingSystem.h>
#include <Core/CoreComponent/UniformRendering.h>
#include <Core\CoreSystem\MaterialSystem.h>
#include <Core/CoreComponent/Transform.h>
#include <Core/CoreComponent/LightComponent.h>
#include "Core/ECS/ECS.h"
#include "Core/Managers/ResourceManager.h"
#include <Rendering/Resource/Cube.h>
#include <Rendering/Resource/Model.h>

using namespace Core::Systems;

RenderingSystem::RenderingSystem(SystemPriority p_priority, double p_updateInterval_ms)
{
	Rendering::Shader::GlobalReloadEvent += BIND(&RenderingSystem::OnReloadShader, this, HOLDER_1);
	m_debugLightMaterial = std::make_shared<Rendering::Material>();
}

RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::Awake()
{
	//This should happen after UniformRenderingSystem Awake because the buffers
	//should be created before binding shaders to them
	auto uniformRenderingComponents = ECS::Get().GetComponents<Components::UniformRendering>();
	if(uniformRenderingComponents.size()> 1)
		LOG(Log::Warning(), "Why do you have more than one uniform rendering component");

	auto theUniformRenderingComponent = std::static_pointer_cast<Components::UniformRendering>(uniformRenderingComponents.begin()->second);	//There should be only one

	auto meshRendererMap = ECS::Get().GetComponents<Components::MeshRenderer>();
	for (auto iterator : meshRendererMap)
	{
		auto meshRendererComponent = std::static_pointer_cast<Components::MeshRenderer>(iterator.second);
		//auto shaderID = meshRendererComponent->Material()->GetShader()->ID();
		auto owner = ECS::Get().m_entityManager->GetEntity(meshRendererComponent->GetOwnerId());
		auto materialRendererComponent = owner->GetComponent<Components::MaterialRenderer>();

		auto shaderID = materialRendererComponent->MaterialSP()->GetShader()->ID();
		theUniformRenderingComponent->CameraUBO().BindShader(shaderID, "CameraData", 0);
		theUniformRenderingComponent->LightUBO().BindShader(shaderID, "LightData", 1);
	}

	auto lightDebugShader = Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("DebugLight");
	m_debugLightMaterial->SetShader(lightDebugShader.get());

	theUniformRenderingComponent->CameraUBO().BindShader(lightDebugShader->ID(), "CameraData", 0);
}

void RenderingSystem::PostUpdate(double p_deltaTime)
{
	auto meshRendererMap = ECS::Get().GetComponents<Components::MeshRenderer>();
	for (auto iterator : meshRendererMap)
	{
		auto meshRenderer = std::static_pointer_cast<Components::MeshRenderer>(iterator.second);
		if (meshRenderer->Model())
		{
			auto owner = ECS::Get().GetEntity(meshRenderer->GetOwnerId());
			auto transform = owner->GetComponent<Components::Transform>();
			auto materialRenderer = owner->GetComponent<Components::MaterialRenderer>();

			materialRenderer->Material().Bind();
			materialRenderer->Material().GetShader()->SetUniformMat4("model", transform->GetTransform());
			materialRenderer->Material().UnBind();

			auto model = meshRenderer->Model();

			if (model->HasSubMeshes())
				Rendering::Renderer::RenderSubModels(model.get(), materialRenderer->MaterialSP());
			else
				Rendering::Renderer::Render(model->Meshes()[0], materialRenderer->MaterialSP());
		}
	}

	auto lights = ECS::Get().GetComponents<Components::LightComponent>();
	auto lightDebugShader = Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("DebugLight");
	for (auto iterator : lights)
	{
		auto lightComponent = std::static_pointer_cast<Components::LightComponent>(iterator.second);
		auto transformComponent = ECS::Get().GetOwner(lightComponent)->GetComponent<Components::Transform>();
		transformComponent->SetScale(CloudMath::Vector3f(0.2f, 0.2f, 0.2f));
		CloudMath::Vector4f lightColor = CloudMath::Vector4f(lightComponent->GetLight()->Diffuse());
		lightDebugShader->Bind();
		lightDebugShader->SetUniformMat4("model", transformComponent->GetTransform());
		lightDebugShader->SetUniformVec4("lightColor", lightColor);
		auto cubeMesh = Cloud::Get().ResourceManager<Rendering::Model>()->GetResource("Cube");
		Rendering::Renderer::Render(cubeMesh->Meshes()[0], m_debugLightMaterial);
		//Rendering::Renderer::Render(*m_debugLightCubeMesh, m_debugLightMaterial);
		lightDebugShader->UnBind();
	}
}

void RenderingSystem::OnReloadShader(Rendering::Shader* p_shader)
{
	auto uniformRenderingComponents = ECS::Get().GetComponents<Components::UniformRendering>();
	auto theUniformRenderingComponent = std::static_pointer_cast<Components::UniformRendering>(uniformRenderingComponents.begin()->second);	//There should be only one
	if (uniformRenderingComponents.size() > 1)
		LOG(Log::Warning(), "Why do you have more than one uniform rendering component");

	theUniformRenderingComponent->CameraUBO().BindShader(p_shader->ID(), "CameraData", 0);
	theUniformRenderingComponent->LightUBO().BindShader(p_shader->ID(), "LightData", 1);
}
