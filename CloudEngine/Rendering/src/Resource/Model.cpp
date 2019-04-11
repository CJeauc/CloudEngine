#include <Rendering/stdafx.h>
#include <Rendering/Resource/Model.h>
#include <Rendering/Resource/Mesh.h>
#include <Rendering/Resource/ModelLoader.h>

using namespace Rendering;

Model::Model()
{
}

Model::Model(std::pair<unsigned int, std::string> p_pair)
{
	//1 model has SubMeshes - 2 model doenst have SubMeshes
	if (p_pair.first == 1)
		m_hasSubMeshes = true;	

	else if (p_pair.first == 2)
		m_hasSubMeshes = false;

	while (!ModelLoader::m_subMeshes.empty())
	{
		AddSubMesh(ModelLoader::m_subMeshes.front());
		ModelLoader::m_subMeshes.pop();
	}

	while (!ModelLoader::m_subMaterials.empty())
	{
		m_materials.push_back(ModelLoader::m_subMaterials.front());
		ModelLoader::m_subMaterials.pop();
	}

	m_name = p_pair.second;
}

Model::~Model()
{
	for (Mesh* mesh : m_meshes)
		delete mesh;

	for (Material* material : m_materials)
		delete material;
}

void Model::AddSubMesh(Mesh* p_mesh)
{
	m_meshes.push_back(p_mesh);
}

std::vector<Mesh*>& Model::Meshes()
{
	return m_meshes;
}

std::vector<Material*>& Rendering::Model::Materials()
{
	return m_materials;
}

bool Rendering::Model::HasSubMeshes() const
{
	return m_hasSubMeshes;
}