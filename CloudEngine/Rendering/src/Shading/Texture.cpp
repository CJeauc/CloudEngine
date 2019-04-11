#include "Rendering/stdafx.h"
#include "Rendering/Shading/Texture.h"

using namespace Rendering;

Texture::Texture()
	: m_ID{0}, m_name {}, m_width {0}, m_height {0}
{
}

Texture::Texture(std::pair<unsigned int, std::string> p_pair)
	: m_ID{p_pair.first}, m_name {p_pair.second}, m_width{ 0 }, m_height{ 0 }
{
}

Texture::~Texture()
{
}

void Texture::Bind(int unit) const
{
	if(unit >= 0)
		glActiveTexture(GL_TEXTURE0 + unit);

	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


unsigned int Texture::ID() const
{
	return m_ID;
}

std::string Texture::Name() const
{
	return m_name;
}
