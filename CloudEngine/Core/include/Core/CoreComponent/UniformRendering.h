#pragma once

#include <Core/CoreAPI.h>
#include <Core/ECS/Component/Component.h>
#include <Rendering/Shading/UniformBuffer.h>

/*
This componenet holds the Uniform Buffers
please refer to the uniform rendering system 
for more details about how data is updated and shared
*/
namespace Core
{
	namespace Components
	{
		class CORE_API UniformRendering : public Component<UniformRendering>
		{
		public:
			void SetProjection(std::shared_ptr<CloudMath::Matrix4f> p_projection);
			static void SetProjectionAspect(float p_aspect);

			Rendering::UniformBuffer& CameraUBO();
			Rendering::UniformBuffer& LightUBO();
			std::shared_ptr<CloudMath::Matrix4f> GetProjection();
		private:
			Rendering::UniformBuffer m_cameraUBO;
			Rendering::UniformBuffer m_lightUBO;
			static std::shared_ptr<CloudMath::Matrix4f> m_projection;

		};
	}
}