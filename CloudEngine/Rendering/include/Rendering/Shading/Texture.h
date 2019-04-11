#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"

namespace Rendering
{
	class RENDERING_API Texture
	{
	public:
		Texture();
		Texture(std::pair<unsigned int, std::string> p_pair);
		Texture(const Texture& p_other) = delete;
		~Texture();

		void Bind(int unit = 0) const;
		void UnBind() const;

		unsigned int ID() const;
		std::string Name() const;

	private:
		unsigned int m_ID;
		std::string m_name;
		unsigned int m_width;
		unsigned int m_height;
	};
}