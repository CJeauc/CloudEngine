#include "Rendering/stdafx.h"
#include "Rendering/Resource/Mesh.h"

// disable warning size_t to GLsizei
#pragma warning(push)
#pragma warning(disable:4267)

using namespace Rendering;

std::vector<CloudMath::Vector3f> MeshData::Positions;
std::vector<CloudMath::Vector3f> MeshData::Normals;
std::vector<CloudMath::Vector2f> MeshData::UV;
std::vector<unsigned int> MeshData::Indices;

Mesh::Mesh()
{
}

Rendering::Mesh::Mesh(std::pair<unsigned int, std::string> p_pair)
{
	if(0 < p_pair.first)
	{
		m_positions = std::move(MeshData::Positions);
		m_normals = std::move(MeshData::Normals);
		m_UV = std::move(MeshData::UV);
		m_indices = std::move(MeshData::Indices);

		m_name = p_pair.second;

		Finalize();
	}
}

Mesh::Mesh(std::vector<CloudMath::Vector3f> p_positions)
	: m_positions {p_positions}
{
	Finalize();
}

Mesh::Mesh(std::vector<CloudMath::Vector3f> p_positions, std::vector<CloudMath::Vector2f> p_UV)
	: m_positions {p_positions} , m_UV {p_UV}
{
	Finalize();
}

Mesh::Mesh(std::vector<CloudMath::Vector3f> p_positions, std::vector<unsigned int> p_indices)
	: m_positions {p_positions} , m_indices {p_indices}
{
	Finalize();
}

Mesh::Mesh(std::vector<CloudMath::Vector3f>& p_positions,
		   std::vector<CloudMath::Vector3f>& p_normals,
		   std::vector<CloudMath::Vector2f>& p_UV,
		   std::vector<unsigned int>& p_indices)
	: m_positions {std::move(p_positions)},
	  m_normals {std::move(p_normals)},
	  m_UV {std::move(p_UV)},
	  m_indices {std::move(p_indices)}
{
	Finalize();
}

Mesh& Mesh::operator=(Mesh&& p_other)
{
	m_positions = std::move(p_other.m_positions);
	m_UV = std::move(p_other.m_UV);
	m_normals = std::move(p_other.m_normals);
	m_indices = std::move(p_other.m_indices);

	std::swap(m_VAO, p_other.m_VAO);
	std::swap(m_VBO, p_other.m_VBO);
	std::swap(m_EBO, p_other.m_EBO);

	return *this;
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);

}

void Mesh::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Finalize()
{
	//Init object id only if not configured before
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

		if (m_UV.size() > 0)
		{
			data.push_back(m_UV[i].x);
			data.push_back(m_UV[i].y);
		}

		if (m_normals.size() > 0)
		{
			data.push_back(m_normals[i].x);
			data.push_back(m_normals[i].y);
			data.push_back(m_normals[i].z);
		}
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	if (m_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	}

	//Calculate stride
	size_t stride = 3 * sizeof(float);

	if (m_UV.size() > 0)
		stride += 2 * sizeof(float);

	if (m_normals.size() > 0)
		stride += 3 * sizeof(float);

	size_t offset = 0;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);

	offset += 3 * sizeof(float);
	if (m_UV.size() > 0)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	}

	offset += 2 * sizeof(float);
	if (m_normals.size() > 0)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	}

	glBindVertexArray(0);

	MeshData::Clear();
}

unsigned int Mesh::VAO() const
{
	return m_VAO;
}

unsigned int Mesh::EBO() const
{
	return m_EBO;
}

unsigned int Mesh::VertexCount() const
{
	return static_cast<unsigned int>(m_positions.size());
}

unsigned int Mesh::IndicesCount() const
{
	return static_cast<unsigned int>(m_indices.size());
}

std::string& Mesh::Name()
{
	return m_name;
}

#pragma warning(pop)