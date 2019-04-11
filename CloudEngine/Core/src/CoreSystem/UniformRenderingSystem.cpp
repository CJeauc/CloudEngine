#include <Core/stdafx.h>
#include <Core/CoreSystem/UniformRenderingSystem.h>
#include <Core/CoreComponent/CameraComponent.h>
#include <Core/ECS/ECS.h>
#include <Core/CoreComponent/LightComponent.h>
#include <Core/CoreComponent/Transform.h>

using namespace Core::Systems;

UniformRenderingSystem::UniformRenderingSystem(SystemPriority p_priority, double p_updateInterval_ms)
{
}

void UniformRenderingSystem::Awake()
{
	auto uniformRenderingComponents = ECS::Get().GetComponents<Components::UniformRendering>();
	for (auto iterator : uniformRenderingComponents)	//There is in theory only one instance created by the engine
	{
		auto uniformRenderingComponent = std::static_pointer_cast<Components::UniformRendering>(iterator.second);
		uniformRenderingComponent->CameraUBO().Create(sizeof(Rendering::CameraData));
		uniformRenderingComponent->LightUBO().Create(sizeof(Rendering::LightData));
	}
}

void UniformRenderingSystem::Update(double p_deltaTime)
{
	auto uniformRenderingComponents = ECS::Get().GetComponents<Components::UniformRendering>();
	auto theUniformRenderingComponent = std::static_pointer_cast<Components::UniformRendering>(uniformRenderingComponents.begin()->second);	//There should be only one

	auto cameras = ECS::Get().GetComponents<Components::CameraComponent>();

	std::shared_ptr<Components::CameraComponent> cameraComp;

	for (auto iterator : cameras)
	{
		cameraComp = std::static_pointer_cast<Components::CameraComponent>(iterator.second);
		if (cameraComp->IsMainCamera())
			break;
	}

	//New Stuff
	auto owner = ECS::Get().GetEntity(cameraComp->GetOwnerId());
	auto transform = owner->GetComponent<Components::Transform>();
	float Cposition[4] = { transform->GetWorldPosition().x, transform->GetWorldPosition().y , transform->GetWorldPosition().z, 0 };

	auto projection = theUniformRenderingComponent->GetProjection();

	theUniformRenderingComponent->CameraUBO().UpdateData(0, sizeof(CloudMath::Vector4f), Cposition);
	auto view = CloudMath::Matrix4f::CreateView(transform->GetWorldPosition(), transform->GetWorldPosition() + transform->GetWorldFront(), transform->GetWorldUp());
	theUniformRenderingComponent->CameraUBO().UpdateData(4 * sizeof(float), sizeof(CloudMath::Matrix4f), view.elements);
	theUniformRenderingComponent->CameraUBO().UpdateData(4 * sizeof(float) + sizeof(CloudMath::Matrix4f), sizeof(CloudMath::Matrix4f), projection->elements);

	//Light

	auto lights = ECS::Get().GetComponents<Components::LightComponent>();

	std::shared_ptr<Components::LightComponent> lightComp;

	for (auto iterator : lights)
	{
		lightComp = std::static_pointer_cast<Components::LightComponent>(iterator.second);
		if (lightComp)
			break;
	}

	auto position = ECS::Get().GetOwner(lightComp)->GetComponent<Components::Transform>()->GetWorldPosition();
	
	theUniformRenderingComponent->LightUBO().UpdateData(0, 4 * sizeof(float), position.elements);
	theUniformRenderingComponent->LightUBO().UpdateData(4 * sizeof(float), 4 * sizeof(float), lightComp->GetLight()->Diffuse().elements);
}
