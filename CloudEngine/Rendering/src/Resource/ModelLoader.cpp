#include <Rendering/stdafx.h>
#include <Rendering/Resource/ModelLoader.h>
#include <CloudMath.h>
#include <Rendering/Shading/TextureLoader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Rendering;

std::queue<Mesh*> ModelLoader::m_subMeshes;
std::queue<Material*> ModelLoader::m_subMaterials;
std::string ModelLoader::m_path;
bool ModelLoader::m_hasSubMeshes = false;

std::pair<unsigned int, std::string> ModelLoader::Load(std::string p_name, std::string p_path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(p_path, aiProcess_Triangulate |
		//aiProcess_FlipUVs |
		aiProcess_PreTransformVertices);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		LOG(Log::Error(), "Failed to load Model at Path: " + p_path);
		return std::pair<unsigned int, std::string>(0, p_name);
	}

	m_path = p_path;
	m_path = m_path.substr(0, m_path.find_last_of("/"));

	// Process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);

	unsigned int materialFlag;

	if (m_hasSubMeshes)
		materialFlag = 1;
	else
		materialFlag = 2;

	m_hasSubMeshes = false;

	return std::pair<unsigned int, std::string>(materialFlag, p_name);
}

void ModelLoader::ProcessNode(aiNode* p_node, const aiScene* p_scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < p_node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene.
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];

		m_subMeshes.push(ProcessMesh(mesh, p_scene));
	}

	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < p_node->mNumChildren; i++)
	{
		m_hasSubMeshes = true;
		ProcessNode(p_node->mChildren[i], p_scene);
	}
}

Mesh* ModelLoader::ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene)
{
	std::vector<CloudMath::Vector3f> positions;
	std::vector<CloudMath::Vector3f> normals;
	std::vector<CloudMath::Vector2f> UV;
	std::vector<unsigned int> indices;

	CloudMath::Vector3f vec3Holder;
	CloudMath::Vector2f vec2Holder;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < p_mesh->mNumVertices; i++)
	{
		// Positions
		vec3Holder.x = p_mesh->mVertices[i].x;
		vec3Holder.y = p_mesh->mVertices[i].y;
		vec3Holder.z = p_mesh->mVertices[i].z;
		positions.push_back(vec3Holder);

		// Normals
		if (p_mesh->HasNormals())
		{
			vec3Holder.x = p_mesh->mNormals[i].x;
			vec3Holder.y = p_mesh->mNormals[i].y;
			vec3Holder.z = p_mesh->mNormals[i].z;
			normals.push_back(vec3Holder);
		}
		else
			normals.push_back(CloudMath::Vector3f(0, 0, 0));

		// Texture Coordinates
		if (p_mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			vec2Holder.x = p_mesh->mTextureCoords[0][i].x;
			vec2Holder.y = p_mesh->mTextureCoords[0][i].y;
			UV.push_back(vec2Holder);
		}
		else
			UV.push_back(CloudMath::Vector2f(0, 0));
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < p_mesh->mNumFaces; i++)
	{
		aiFace face = p_mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//Process Materials //what if some submeshes dont have material ?
	if (p_mesh->mMaterialIndex > 0)
	{
		aiString str;
		aiTextureType type = aiTextureType_DIFFUSE;

		aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];

		material->GetTexture(type, 0, &str);

		if (str.length > 0)
			m_subMaterials.push(ProcessMaterial(material));
	}

	return new Mesh(positions, normals, UV, indices);
}

Material* ModelLoader::ProcessMaterial(aiMaterial* p_material)
{
	Material* material = new Material();
	aiString str;
	aiTextureType type;
	std::string path;

	//Diffuse;
	type = aiTextureType_DIFFUSE;
	p_material->GetTexture(type, 0, &str);
	path = m_path + "/" + str.C_Str();
	Texture* textureDiffuse = new Texture(TextureLoader::Load(str.C_Str(), path));
	Uniform* uniformDiffuse = new Uniform();
	uniformDiffuse->Type = SHADER_TYPE::SAMPLER2D;
	uniformDiffuse->Name = str.C_Str();
	material->AddSlot(std::pair<Uniform*, Texture*>(uniformDiffuse, textureDiffuse));

	//Specular
	type = aiTextureType_SPECULAR;
	p_material->GetTexture(type, 0, &str);
	path = m_path + "/" + str.C_Str();
	Texture* textureSpecular = new Texture(TextureLoader::Load(str.C_Str(), path));
	Uniform* uniformSpecular = new Uniform();
	uniformSpecular->Type = SHADER_TYPE::SAMPLER2D;
	uniformSpecular->Name = str.C_Str();

	material->AddSlot(std::pair<Uniform*, Texture*>(uniformSpecular, textureDiffuse));

	return material;
}
