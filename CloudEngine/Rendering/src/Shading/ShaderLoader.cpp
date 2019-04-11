#include "Rendering/stdafx.h"
#include "Rendering/Shading/ShaderLoader.h"

using namespace Rendering;

std::pair<unsigned int, std::string> ShaderLoader::Load(std::string p_name, std::string p_shaderPath)
{
	std::pair<unsigned int, std::string> shaderData;

	std::ifstream vertexShadeFile, fragmentShaderFile;
	vertexShadeFile.open(p_shaderPath + ".vs");
	fragmentShaderFile.open(p_shaderPath + ".fs");

	if (!vertexShadeFile.is_open() || !fragmentShaderFile.is_open())
	{
		LOG(Log::Warning(), "Shader failed to load, Check your Path");
		return std::pair<unsigned int, std::string>(0, "Error");
	}

	std::string vertexShadeSouce = ReadShaderFile(vertexShadeFile);
	std::string fragmentShaderSource = ReadShaderFile(fragmentShaderFile);

	shaderData.first = Create(vertexShadeSouce, fragmentShaderSource);
	shaderData.second = p_name;

	vertexShadeFile.close();
	fragmentShaderFile.close();

	return shaderData;
}

unsigned int ShaderLoader::Create(std::string p_vertexShaderSource, std::string p_fragmentShaderSource)
{
	unsigned int shaderID;

	const unsigned int vs = Compile(GL_VERTEX_SHADER, p_vertexShaderSource);
	if (vs == 0)
		LOG(Log::Error(), "VSShader compilation Failed");

	const unsigned int fs = Compile(GL_FRAGMENT_SHADER, p_fragmentShaderSource);
	if (fs == 0)
		LOG(Log::Error(), "FSShader compilation Failed");

	shaderID = glCreateProgram();

	glAttachShader(shaderID, vs);
	glAttachShader(shaderID, fs);
	glLinkProgram(shaderID);
	glValidateProgram(shaderID);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		LOG(Log::Error(), "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog);
	}

	(glDeleteShader(vs));
	(glDeleteShader(fs));

	return shaderID;
}

int ShaderLoader::Compile(const unsigned int p_type, const std::string & p_sourceCode)
{
	const char* src = p_sourceCode.c_str();
	int result;

	const unsigned int id = glCreateShader(p_type);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		auto* message = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);

		LOG(Log::Error(), "Failed to compile " << (p_type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << " shader\n" << message);

		glDeleteShader(id);

		return 0;
	}

	return id;
}

std::string ShaderLoader::ReadShaderFile(std::ifstream& p_file)
{
	std::string line;
	std::stringstream stringStream;

	while (getline(p_file, line))
	{
		stringStream << line << "\n";
	}

	return stringStream.str();
}
