#include "Core/stdafx.h"

#include "Core/Engine/CloudEngine.h"
#include "Core/Engine/Input.h"
#include "Rendering/Shading/Shader.h"
#include "Rendering/Resource/Cube.h"
#include <Rendering/Resource/ModelLoader.h>

#include "Core/Managers/Register.h"
#include "Core/Managers/ResourceManager.h"

/*ECS TEST*/
#include "Core/ECS/ECS.h"
#include <Core/CoreSystem/InputTestSystem.h>
#include <Core/CoreComponent/Transform.h>
#include <Core/CoreEntity/GameObject.h>
#include <Core/CoreSystem/RenderingSystem.h>
#include <Core/CoreSystem/UniformRenderingSystem.h>
#include <Core/CoreComponent/UniformRendering.h>
#include <Core/CoreSystem/MaterialSystem.h>
#include <Core/CoreSystem/CameraSystem.h>
#include <Core/CoreSystem/FPCameraSystem.h>
#include "Core/CoreSystem/WorldTransformSystem.h"
#include <Core/CoreComponent/LightComponent.h>
#include <Core/CoreSystem/LightSwitcherSystem.h>
#include <Core/CoreSystem/PhysicSystem.h>
#include <Core/Scene/SceneManager.h>
#include <Core/CoreEntity/Daemon.h>

using namespace Core;

double CloudEngine::DeltaTime = 0;

CloudEngine::CloudEngine()
	: lastFrame{0}, m_window{1080, 720} {}

CloudEngine::~CloudEngine() {}

void CloudEngine::Init(bool p_useWindow)
{
	if (p_useWindow)
	{
		ASSERTD(m_window.Create(), "Failed To Create window");
	}

	ASSERTD(m_renderer.InitGlad(), "Failed To Load Driver");
	
	SceneManagement::SceneManager::AddScene("Scene06");

	BindInput();

	Setup();

	SLOG(Log::Info(), "Cloud Engine Up and Running\n");
}

void CloudEngine::Awake()
{
	ECS::Get().Awake();
}

void CloudEngine::Setup()
{
	REGISTER_RES(Rendering::Shader, &Rendering::ShaderLoader::Load);
	REGISTER_RES(Rendering::Texture, &Rendering::TextureLoader::Load);
	//REGISTER_RES(Rendering::Mesh, &Rendering::MeshLoader::Load);
	REGISTER_RES(Rendering::Model, &Rendering::ModelLoader::Load);

	m_renderer.SetClearColor(0.160784f, 0.309803f, 0.478431f, 1.0f);

	Cloud::Get().ResourceManager<Rendering::Shader>()->Load("Default", "simple");
	Cloud::Get().ResourceManager<Rendering::Shader>()->Load("DebugLight", "light");
	Cloud::Get().ResourceManager<Rendering::Texture>()->Load("Red", "colors/red.jpg");
	Cloud::Get().ResourceManager<Rendering::Texture>()->Load("Checker", "checker.jpg");
	Cloud::Get().ResourceManager<Rendering::Texture>()->Load("BoxDiffuse", "box_diffuse.png");
	Cloud::Get().ResourceManager<Rendering::Texture>()->Load("BoxSpecular", "box_specular.png");

	Cloud::Get().ResourceManager<Rendering::Model>()->Load("Cube", "Primitives/Cube.fbx");
	Cloud::Get().ResourceManager<Rendering::Model>()->Load("Cylinder", "Primitives/Cylinder.fbx");
	Cloud::Get().ResourceManager<Rendering::Model>()->Load("Sphere", "Primitives/Sphere.fbx");
	Cloud::Get().ResourceManager<Rendering::Model>()->Load("Torus", "Primitives/Torus.fbx");
	Cloud::Get().ResourceManager<Rendering::Model>()->Load("nanosuit", "nanosuit.obj");

	/*Core Systems*/
	auto inputTestSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::InputTestSystem>();
	auto uniformRenderingSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::UniformRenderingSystem>();
	auto renderingSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::RenderingSystem>();
	auto materialSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::MaterialSystem>();
	// auto cameraSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::CameraSystem>();
	//auto fpCameraSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::FPCameraSystem>();
	auto lightSwitcherSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::LightSwitcherSystem>();
	auto physicSystem = ECS::Get().m_systemManager->AddSystem<Core::Systems::PhysicSystem>();

	// uniformRenderingSystem->AddDependencies(cameraSystem);
	//uniformRenderingSystem->AddDependencies(fpCameraSystem);
	renderingSystem->AddDependencies(uniformRenderingSystem);

	//Setting Core Systems
	ECS::Get().m_systemManager->SetAsCore<Core::Systems::UniformRenderingSystem>();
	ECS::Get().m_systemManager->SetAsCore<Core::Systems::RenderingSystem>();
	ECS::Get().m_systemManager->SetAsCore<Core::Systems::MaterialSystem>();
	// ECS::Get().m_systemManager->SetAsCore<Core::Systems::CameraSystem>();
	ECS::Get().m_systemManager->SetAsCore<Core::Systems::PhysicSystem>();

	//Daemons
	auto uniformDaemon = ECS::Get().CreateEntity<Core::Entities::Daemon>("UniformDaemon");
	auto uniformRenderingDaemonComp = uniformDaemon->AddComponent<Core::Components::UniformRendering>();

	CloudMath::Matrix4f projection = CloudMath::Matrix4f::CreatePerspective(45, m_window.AspectRatio(), 0.1f, 100.0f);

	//Camera
	//auto myCamera = ECS::Get().CreateEntity<Core::Entities::Daemon>("Camera");
	//auto cameraComponent = myCamera->AddComponent<Core::Components::CameraComponent>(true);
	//fpCameraSystem->AttachCamera(cameraComponent);

	auto nano = CreateNanoEntity("", CloudMath::Vector3f(0, 0, -10));

	//Light
	auto pointLight = ECS::Get().CreateEntity<Core::Entities::Daemon>("Point Light");
	auto lightComponent = pointLight->AddComponent<Core::Components::LightComponent>();
	auto lightTransform = pointLight->GetComponent<Components::Transform>();
	lightTransform->SetPosition(CloudMath::Vector3f(1, 3, -3));
	lightComponent->SetColor(CloudMath::Vector3f(1, 0.5f, 1));

	inputTestSystem->AttachTransform(lightTransform);

	uniformRenderingDaemonComp->SetProjection(std::make_shared<CloudMath::Matrix4f>(projection));
	Input::SetMouseUpdate(false);
}

void CloudEngine::Frame()
{
	double currentFrame = glfwGetTime();
	DeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	m_renderer.BeginFrame();

	Input::Process();

	ECS::Get().m_systemManager->FixedUpdate(DeltaTime);
	ECS::Get().m_systemManager->PreUpdate(DeltaTime);
	ECS::Get().m_systemManager->Update(DeltaTime);
	ECS::Get().m_systemManager->PostUpdate(DeltaTime);

	m_window.SwapBuffers();

	Input::SetMouseUpdate(true);
}

void CloudEngine::Frame(double p_timeElapsed)
{
	double currentFrame = p_timeElapsed;
	DeltaTime = (currentFrame - lastFrame) * 0.001;
	lastFrame = currentFrame;
	m_renderer.BeginFrame();

	Input::Process();

	ECS::Get().m_systemManager->FixedUpdate(DeltaTime);
	ECS::Get().m_systemManager->PreUpdate(DeltaTime);
	ECS::Get().m_systemManager->Update(DeltaTime);
	ECS::Get().m_systemManager->PostUpdate(DeltaTime);
}

std::shared_ptr<Core::Entities::GameObject> CloudEngine::CreateCubeEntity(
	std::string p_name, CloudMath::Vector3f p_position) 
{
	auto material = std::make_shared<Rendering::Material>(Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("Default").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("diffuseTex"),
	                          Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxDiffuse").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("specularTex"),
	                          Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxSpecular").get());


	std::shared_ptr<Core::Entities::GameObject> cube = ECS::Get().CreateEntity<Core::Entities::GameObject>(p_name);
	
	auto materialRendererComponent = cube->AddComponent<Core::Components::MaterialRenderer>(material);

	auto transformComponent = cube->GetComponent<Core::Components::Transform>();
	transformComponent->SetPosition(p_position);

	auto meshRendererComponent = cube->GetComponent<Core::Components::MeshRenderer>();

	meshRendererComponent->SetModel(Cloud::Get().ResourceManager<Rendering::Model>()->GetResource("Cube"));

	return cube;
}

std::shared_ptr<Core::Entities::GameObject> CloudEngine::CreateSphereEntity(std::string p_name,
	CloudMath::Vector3f p_position) 
{
	auto material = std::make_shared<Rendering::Material>(Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("Default").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("diffuseTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxDiffuse").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("specularTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxSpecular").get());


	std::shared_ptr<Core::Entities::GameObject> sphere = ECS::Get().CreateEntity<Core::Entities::GameObject>(p_name);
	auto materialRendererComponent = sphere->AddComponent<Core::Components::MaterialRenderer>(material);

	auto transformComponent = sphere->GetComponent<Core::Components::Transform>();
	transformComponent->SetPosition(p_position);

	auto meshRendererComponent = sphere->GetComponent<Core::Components::MeshRenderer>();

	meshRendererComponent->SetModel(Cloud::Get().ResourceManager<Rendering::Model>()->GetResource("Sphere"));

	return sphere;
}

std::shared_ptr<Core::Entities::GameObject> CloudEngine::CreateNanoEntity(std::string p_name,
	CloudMath::Vector3f p_position) 
{
	//Testing Sub Meshes
	auto material = std::make_shared<Rendering::Material>(Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("Default").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("diffuseTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxDiffuse").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("specularTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxSpecular").get());

	std::shared_ptr<Core::Entities::GameObject> nano = Core::ECS::Get().CreateEntity<Core::Entities::GameObject>("Nano");
	auto materialRendererComponent = nano->AddComponent<Core::Components::MaterialRenderer>(material);

	auto transformComponent = nano->GetComponent<Core::Components::Transform>();
	transformComponent->SetScale(CloudMath::Vector3f(0.3f, 0.3f, 0.3f));
	transformComponent->SetPosition(p_position);

	auto meshRendererComponent = nano->GetComponent<Core::Components::MeshRenderer>();

	auto modelNano = Cloud::Get().ResourceManager<Rendering::Model>()->GetResource("Nano");
	if (!modelNano)
	{
		Cloud::Get().ResourceManager<Rendering::Model>()->Load("Nano", "nanosuit.obj");
		modelNano = Cloud::Get().ResourceManager<Rendering::Model>()->GetResource("Nano");
	}

	meshRendererComponent->SetModel(modelNano);

	return nano;
}

std::shared_ptr<Core::Entities::GameObject> CloudEngine::CreateGameObject(std::string p_name, CloudMath::Vector3f p_position, std::string p_type)
{
	auto material = std::make_shared<Rendering::Material>(Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("Default").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("diffuseTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxDiffuse").get());
	material->SetTextureToSlot(material->GetTextureSlotByName("specularTex"),
		Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxSpecular").get());


	std::shared_ptr<Core::Entities::GameObject> gameObject = ECS::Get().CreateEntity<Core::Entities::GameObject>(p_name);
	auto materialRendererComponent = gameObject->AddComponent<Core::Components::MaterialRenderer>(material);

	auto transformComponent = gameObject->GetComponent<Core::Components::Transform>();
	transformComponent->SetPosition(p_position);

	auto meshRendererComponent = gameObject->GetComponent<Core::Components::MeshRenderer>();

	meshRendererComponent->SetModel(Cloud::Get().ResourceManager<Rendering::Model>()->GetResource(p_type));

	return gameObject;
}

bool Core::CloudEngine::Running()
{
	return !m_window.ShouldClose();
}

void CloudEngine::BindInput()
{
	glfwSetKeyCallback(m_window.GLFWWindow(), Input::KeyCallBack);
	glfwSetCursorPosCallback(m_window.GLFWWindow(), Input::MouseCallBack);
	glfwSetMouseButtonCallback(m_window.GLFWWindow(), Input::MouseButtonCallBack);
}
