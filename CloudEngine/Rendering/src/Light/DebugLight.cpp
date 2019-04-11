#include "Rendering/stdafx.h"
#include "Rendering/Light/DebugLight.h"

// disable warning size_t to GLsizei
#pragma warning(push)
#pragma warning(disable: 4267)

using namespace Rendering;

DebugLight::DebugLight()
	: m_color { CloudMath::Vector4f(1, 1, 0.4f, 1) }
{
}

void DebugLight::Create()
{
	m_positions = std::vector<CloudMath::Vector3f>{

		CloudMath::Vector3f(-0.5f, -0.5f,  0.5f),		//Front
		CloudMath::Vector3f(0.5f, -0.5f,  0.5f),
		CloudMath::Vector3f(0.5f,  0.5f,  0.5f),
		CloudMath::Vector3f(-0.5f,  0.5f,  0.5f),

		CloudMath::Vector3f(-0.5f, -0.5f, -0.5f),		//Back
		CloudMath::Vector3f(0.5f, -0.5f, -0.5f),
		CloudMath::Vector3f(0.5f,  0.5f, -0.5f),
		CloudMath::Vector3f(-0.5f,  0.5f, -0.5f)
	};

	m_indices = std::vector<unsigned int>{

		0, 1, 2,		//Front
		2, 3, 0,

		1, 5, 6,		//Right
		6, 2, 1,

		7, 6, 5,		//Back
		5, 4, 7,

		4, 0, 3,		//Left
		3, 7, 4,

		4, 5, 1,		//Bottom
		1, 0, 4,

		3, 2, 6,		//Top
		6, 7, 3
	};

	Finalize();
}

void DebugLight::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}

void DebugLight::Free()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void DebugLight::SetColor(CloudMath::Vector4f p_color)
{
	m_color = p_color;
}

CloudMath::Vector4f& DebugLight::Color()
{
	return m_color;
}

/*Carefull with this, as it will delete mesh from GPU*/
void DebugLight::Finalize()
{
	if (!m_VAO)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
	}

	std::vector<float> data;

	for (int i = 0; i < m_positions.size(); ++i)
	{
		data.push_back(m_positions[i].x);
		data.push_back(m_positions[i].y);
		data.push_back(m_positions[i].z);
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	if (m_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glBindVertexArray(0);
}

#pragma warning(pop)