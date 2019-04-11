#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "CloudMath.h"

namespace Rendering
{

#ifndef UNIFORMDATA
#define UNIFORMDATA
	struct RENDERING_API CameraData
	{
		float position[4];
		CloudMath::Matrix4f view;
		CloudMath::Matrix4f projection;
	};

	struct RENDERING_API LightData
	{
		float position[4];
		float diffuse[4];
		
	};

#endif
	class RENDERING_API UniformBuffer
	{
	public:
		UniformBuffer();

		void Create(unsigned int p_size);
		void UpdateData(unsigned int p_offset, unsigned int p_size, void* p_data);
		void BindShader(unsigned int p_shaderID, const std::string& p_name, unsigned int p_slot);		

	private:
		unsigned int m_uboID;

	};
}