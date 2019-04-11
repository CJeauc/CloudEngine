#include <Core/stdafx.h>
#include <Core/CoreComponent/MeshRenderer.h>
#include <Core\CoreComponent\CameraComponent.h>

using namespace Core::Components;

CameraComponent::CameraComponent(bool p_mainCamera, float p_speed, float p_sensitivity, float p_zoom)
	: m_mainCamera {p_mainCamera}, m_movementSpeed(p_speed), m_sensitivity(p_sensitivity), m_zoom(p_zoom)
{
}

CameraComponent::~CameraComponent()
{
}


bool CameraComponent::IsMainCamera()
{
	return m_mainCamera;
}

void CameraComponent::SetMainCamera(bool p_mainCamera)
{
	m_mainCamera = p_mainCamera;
}
