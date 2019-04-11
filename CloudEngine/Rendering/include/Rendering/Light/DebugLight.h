#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
//#include "Rendering/Resource/Mesh.h"
#include "CloudMath.h"


namespace Rendering
{
	class RENDERING_API DebugLight
	{
	public:
		DebugLight();

		void Create();
		void Draw();
		void Free();

		void SetColor(CloudMath::Vector4f p_color);
		CloudMath::Vector4f& Color();

	private:
		void Finalize();

	protected:
		std::vector<CloudMath::Vector3f> m_positions;
		std::vector<unsigned int> m_indices;
		CloudMath::Vector4f m_color;

		unsigned int m_VAO = 0;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}