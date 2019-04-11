#include "Rendering/stdafx.h"
#include "Rendering/Shading/TextureLoader.h"
#include "stb_image.h"

using namespace Rendering;

std::pair<unsigned int, std::string> TextureLoader::Load(std::string p_name, std::string p_texturePath)
{
	std::pair<unsigned int, std::string> textureData;

	stbi_set_flip_vertically_on_load(true);
	
	int width, height, nrComponents;

	unsigned char* data = stbi_load(p_texturePath.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
			
		else if (nrComponents == 4)
			format = GL_RGBA;

		textureData.first = Generate(width, height, 0, format, GL_UNSIGNED_BYTE, data);

	}
	else
	{
		LOG(Log::Error(), "Failed to load Texture at Path " << p_texturePath);
	}

	stbi_image_free(data);

	textureData.second = p_name;

	return textureData;
}

unsigned int TextureLoader::Generate(unsigned int p_width, unsigned int p_height, GLenum p_internalFormat, GLenum p_format, GLenum p_type, unsigned char* p_data)
{
	unsigned int id;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, p_format, p_width, p_height, 0, p_format, GL_UNSIGNED_BYTE, p_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	return id;
}
