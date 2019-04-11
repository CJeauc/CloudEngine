#pragma once

#include <Rendering/RenderingAPI.h>
#include <Rendering/Resource/Model.h>

/*Forward Declaration Assimp*/
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiString;

namespace Rendering
{
	class RENDERING_API ModelLoader
	{
	public:
		static std::pair<unsigned int, std::string> Load(std::string p_name, std::string p_path);

	private:
		static void ProcessNode(aiNode* p_node, const aiScene* p_scene);
		static Mesh* ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene);
		static Material* ProcessMaterial(aiMaterial* p_material);

		friend class Model;
		static std::queue<Mesh*> m_subMeshes;
		static std::queue<Material*> m_subMaterials;	//what if some submeshes dont have material ?

		static std::string m_path;
		static bool m_hasSubMeshes;
	};
}