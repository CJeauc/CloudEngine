#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "CloudMath.h"

namespace Rendering
{
	struct RENDERING_API MeshData
	{
		static std::vector<CloudMath::Vector3f> Positions;
		static std::vector<CloudMath::Vector3f> Normals;
		static std::vector<CloudMath::Vector2f> UV;
		static std::vector<unsigned int> Indices;

		static void Clear()
		{
			Positions.clear();
			Normals.clear();
			UV.clear();
			Indices.clear();
		}
	};

	class RENDERING_API Mesh
	{
	public:
		Mesh();
		Mesh(std::pair<unsigned int, std::string> p_pair);
		Mesh(std::vector<CloudMath::Vector3f> p_positions);
		Mesh(std::vector<CloudMath::Vector3f> p_positions, std::vector<CloudMath::Vector2f> p_UV);
		Mesh(std::vector<CloudMath::Vector3f> p_positions, std::vector<unsigned int> p_indices);
		Mesh(std::vector<CloudMath::Vector3f>& p_positions,
			 std::vector<CloudMath::Vector3f>& p_normals,
			 std::vector<CloudMath::Vector2f>& p_UV,
			 std::vector<unsigned int>& p_indices
			 );

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		Mesh& operator=(Mesh&& p_other);

		~Mesh();

		void Draw();

		void Finalize();

		unsigned int VAO() const;
		unsigned int EBO() const;
		unsigned int VertexCount() const;
		unsigned int IndicesCount() const;

		std::string& Name();

	protected:
		std::vector<CloudMath::Vector3f> m_positions;
		std::vector<CloudMath::Vector2f> m_UV;
		std::vector<CloudMath::Vector3f> m_normals;
		//TODO:: Add normals, tangeants, bitangeants

		std::vector<unsigned int> m_indices;

		unsigned int m_VAO = 0;
		unsigned int m_VBO;
		unsigned int m_EBO;

		std::string m_name;
	};
}
