#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "Rendering/Shading/Texture.h"

namespace Rendering
{
	class RENDERING_API TextureLoader
	{
	public:
		static std::pair<unsigned int, std::string> Load(std::string p_name, std::string p_texturePath);

	private:
		static unsigned int Generate(unsigned int p_width, unsigned int p_height, GLenum p_internalFormat, GLenum p_format, GLenum p_type, unsigned char* p_data);
	};
}