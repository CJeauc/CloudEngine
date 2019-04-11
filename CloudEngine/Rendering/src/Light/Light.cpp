#include "Rendering/stdafx.h"
#include "Rendering/Light/Light.h"

using namespace Rendering;

Light::Light()
{
}

Light::~Light()
{
}

void Light::SetPosition(const CloudMath::Vector3f& p_position)
{
	m_position = p_position;
}

void Light::SetDiffuse(const CloudMath::Vector3f& p_diffuse)
{
	m_diffuse = p_diffuse;
}

CloudMath::Vector3f Light::Position() const
{
	return m_position;
}

CloudMath::Vector3f Light::Diffuse() const
{
	return m_diffuse;
}

