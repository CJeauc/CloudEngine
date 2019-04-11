#pragma once

#include <Rendering/RenderingAPI.h>
#include <Rendering/Resource/Mesh.h>
#include <Rendering/Shading/Material.h>

namespace Rendering
{
	class RENDERING_API Model
	{
	public:
		Model();
		Model(std::pair<unsigned int, std::string> p_pair);
		~Model();

		void AddSubMesh(Mesh* p_mesh);
		std::vector<Mesh*>& Meshes();
		std::vector<Material*>& Materials();

		bool HasSubMeshes() const;
		void SetHasSubMeshes(bool p_hasSubMeshes)
		{
			m_hasSubMeshes = p_hasSubMeshes;
		}

		std::string& Name()
		{
			return m_name;
		}

	private:
		std::vector<Mesh*> m_meshes;
		std::vector<Material*> m_materials;
		bool m_hasSubMeshes;
		std::string m_name;
	};
}