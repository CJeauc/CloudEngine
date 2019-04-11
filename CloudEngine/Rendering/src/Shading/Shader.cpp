
#include "Rendering/stdafx.h"
#include "Rendering/Shading/Shader.h"
#include "Tools.h"

// disable warning comparison signed/unsigned (can't change because opengl need it)
#pragma warning(push)
#pragma warning(disable: 4018)

using namespace Rendering;

Tools::Event<Shader*> Shader::GlobalReloadEvent;

Shader::Shader()
	: m_ID {0}, m_name{}
{
}

Shader::Shader(std::pair<unsigned int, std::string> p_pair)
	: m_ID{ p_pair.first }, m_name{ p_pair.second }
{
	Bind();
	QueryUniformsAndAttributes();
	UnBind();
}

Shader::~Shader()
{
	if(m_ID != std::numeric_limits<unsigned int>::max())
		DeleteProgram();
}

Shader& Shader::operator=(Shader&& p_other)
{
	DeleteProgram();

	m_ID = p_other.m_ID;
	m_name = p_other.m_name;
	m_uniforms = p_other.m_uniforms;
	m_attributes = p_other.m_attributes;

	p_other.m_ID = std::numeric_limits<unsigned int>::max();

	ReloadEvent.Invoke(this);
	GlobalReloadEvent.Invoke(this);

	return *this;
}

void Shader::Bind() const
{
	glUseProgram(m_ID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::DeleteProgram() const
{
	glDeleteProgram(m_ID);
}

void Shader::SetUniformMat4(const std::string& p_name, const CloudMath::Matrix4f& p_Matrix)
{
	int loc = GetUniformLocation(p_name);

	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, p_Matrix.elements);
	else
		LOG(Log::Error(), "Shader " + m_name + " does not have UniformMat4 \"" + p_name + "\"");
}

void Shader::SetUniformInt(const std::string& p_name, int p_value)
{
	int loc = GetUniformLocation(p_name);

	if (loc >= 0)
		glUniform1i(loc, p_value);
	else
		LOG(Log::Error(), "Shader " + m_name + " does not have int \"" + p_name + "\"");
}

void Shader::SetUniformVec4(const std::string& p_name, const CloudMath::Vector4f& p_vec4)
{
	int loc = GetUniformLocation(p_name);
	
	if (loc >= 0)
		glUniform4f(loc, p_vec4.x, p_vec4.y, p_vec4.z, p_vec4.w);
	else
		LOG(Log::Error(), "Shader " + m_name + " does not have Uniform4f \"" + p_name + "\"");
}

void Shader::SetUniformVec3(const std::string& p_name, const CloudMath::Vector3f& p_vec3)
{
	int loc = GetUniformLocation(p_name);

	if (loc >= 0)
		glUniform3f(loc, p_vec3.x, p_vec3.y, p_vec3.z);
	else
		LOG(Log::Error(), "Shader " + m_name + " does not have Uniform3f \"" + p_name + "\"");
}

unsigned int Shader::ID() const
{
	return m_ID;
}

void Shader::QueryUniformsAndAttributes()
{
	int nrAttributes, nrUniforms;
	glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
	glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);

	m_attributes.resize(nrAttributes);
	m_uniforms.resize(nrUniforms);

	// iterate over all active attributes
	char buffer[256];
	for (unsigned int i = 0; i < nrAttributes; ++i)
	{
		GLenum glType;
		glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, &m_attributes[i].Size, &glType, buffer);
		m_attributes[i].Name = std::string(buffer);
		m_attributes[i].Type = static_cast<SHADER_TYPE>(glType);
		m_attributes[i].Location = glGetAttribLocation(m_ID, buffer);
	}

	// iterate over all active uniforms
	for (unsigned int i = 0; i < nrUniforms; ++i)
	{
		GLenum glType;
		glGetActiveUniform(m_ID, i, sizeof(buffer), 0, &m_uniforms[i].Size, &glType, buffer);
		m_uniforms[i].Name = std::string(buffer);
		m_uniforms[i].Type = static_cast<SHADER_TYPE>(glType);
		m_uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
	}
}

int Shader::GetUniformLocation(std::string p_name)
{
	for (unsigned int i = 0; i < m_uniforms.size(); ++i)
	{
		if (m_uniforms[i].Name == p_name)
			return m_uniforms[i].Location;
	}
	return -1;
}

#pragma warning(pop)