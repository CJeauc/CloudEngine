#include <Core/stdafx.h>
#include <Core/CoreSystem/CameraSystem.h>
#include <Core/ECS/ECS.h>
#include <Core/CoreComponent/Transform.h>

using namespace Core::Systems;

CameraSystem::CameraSystem(Core::SystemPriority p_priority, double p_updateInterval_ms) {}

void CameraSystem::Awake()
{
	auto uniformRenderingComponents = ECS::Get().GetComponents<Components::UniformRendering>();

	if (uniformRenderingComponents.size() > 1) //There should be only one created by CloudEngine
		LOG(Log::Error(), "Why do you have more than one uniform rendering component");

	m_uniformRendering = std::static_pointer_cast<Components::UniformRendering>(
		uniformRenderingComponents.begin()->second); //There should be only one
	if (!m_uniformRendering)
		LOG(Log::Error(), "Camera System cant find uniform renderring component");

	auto camerasMap = ECS::Get().GetComponents<Components::CameraComponent>();
	for (auto iterator : camerasMap)
	{
		auto cameraComponent = std::static_pointer_cast<Components::CameraComponent>(iterator.second);

		if (cameraComponent->IsActive())
		{
			m_mainCamera = cameraComponent;
			break;
		}
	}

	//m_uniformRendering->SetCamera(m_mainCamera->GetCamera());
}

void CameraSystem::PreUpdate(double p_deltaTime)
{
}

void CameraSystem::Update(double p_deltaTime)
{
	//float yaw = m_mainCamera->GetCamera()->Yaw();
	//float pitch = m_mainCamera->GetCamera()->Pitch();
	auto owner = ECS::Get().GetEntity(m_mainCamera->GetOwnerId());

	auto transform = owner->GetComponent<Components::Transform>();
	//transform->SetPosition(m_mainCamera->GetCamera()->Position());
	//transform->SetRotation(CloudMath::Vector3f(pitch, yaw, 0));
}

std::shared_ptr<Core::Components::CameraComponent> CameraSystem::GetMainCamera()
{
	return m_mainCamera;
}
