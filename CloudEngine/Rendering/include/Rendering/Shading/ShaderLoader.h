#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "Rendering/Shading/Shader.h"

namespace Rendering
{
	/*
	 * This is a utility class that loads the shader into the GPU
	 * Be carefull to always store the return of Load into a shader
	 * Failing to do so will generate a GPU Leak of a shader program
	 * @param p_shaderPath without extention, the vertex and the fragment must have the same name
	*/
	class RENDERING_API ShaderLoader
	{
	public:
		static std::pair<unsigned int, std::string> Load(std::string p_name, std::string p_shaderPath);
		

	private:
		static std::string ReadShaderFile(std::ifstream& p_file);
		static unsigned int Create(std::string p_vertexShaderSource, std::string p_fragmentShaderSource);
		static int Compile(const unsigned int p_type, const std::string& p_sourceCode);
	};
}