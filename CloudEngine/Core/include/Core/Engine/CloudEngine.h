#pragma once

#include "Core/CoreAPI.h"
#include "Rendering.h"
#include "Core/Window/Window.h"

#include "Rendering/Resource/Mesh.h"
#include "Rendering/Shading/ShaderLoader.h"
#include "Rendering/Shading/Textureloader.h"
#include "Rendering/Shading/Material.h"
#include "Rendering/Shading/UniformBuffer.h"
#include "Rendering/Light/Light.h"

#include <Core/ECS/ECS.h>

//#include <Core/Scene/Scene.h>

namespace Core
{
	class CORE_API CloudEngine
	{
	public:

		CloudEngine();
		~CloudEngine();

		void Init(bool p_useWindow = false);

		void Awake();

		void Frame();
		void Frame(double p_timeElapsed);

		static std::shared_ptr<Core::Entities::GameObject> CreateSphereEntity(std::string p_name, CloudMath::Vector3f p_position);
		static std::shared_ptr<Core::Entities::GameObject> CreateNanoEntity(std::string p_name, CloudMath::Vector3f p_position);
		static std::shared_ptr<Core::Entities::GameObject> CreateCubeEntity(std::string p_name, CloudMath::Vector3f p_position);
		static std::shared_ptr<Core::Entities::GameObject> CreateGameObject(std::string p_name, CloudMath::Vector3f p_position, std::string p_type);

		bool Running();

	private:
		void Setup();
		void BindInput();
		
	public:
		static double DeltaTime;
		double lastFrame;


	private:
		Window m_window;
		Rendering::Renderer m_renderer;
	};
}