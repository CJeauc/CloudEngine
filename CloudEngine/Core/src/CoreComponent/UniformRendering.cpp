#include <Core/stdafx.h>
#include <Core/CoreComponent/UniformRendering.h>

using namespace Core::Components;

std::shared_ptr<CloudMath::Matrix4f> UniformRendering::m_projection;

void UniformRendering::SetProjection(std::shared_ptr<CloudMath::Matrix4f> p_projection)
{
	m_projection = p_projection;
}

void Core::Components::UniformRendering::SetProjectionAspect(float p_aspect)
{
	//TODO FOV, Near & Far Should be settings from the active camera and not hard coded 
	m_projection = std::make_shared<CloudMath::Matrix4f>(CloudMath::Matrix4f::CreatePerspective(45, p_aspect, 0.1f, 100.0f));
}

Rendering::UniformBuffer& UniformRendering::CameraUBO()
{
	return m_cameraUBO;
}

Rendering::UniformBuffer& UniformRendering::LightUBO()
{
	return m_lightUBO;
}

std::shared_ptr<CloudMath::Matrix4f> Core::Components::UniformRendering::GetProjection()
{
	return m_projection;
}
