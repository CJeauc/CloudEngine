#include <Core/stdafx.h>
#include <Core/CoreComponent/MeshRenderer.h>
#include <Rendering.h>
#include <Core/Engine/Cloud.h>
#include <Core/Managers/ResourceManager.h>

using namespace Core::Components;
using namespace TinyXML2;

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode* p_parent) const
{
	XMLElement* meshRenderer = p_doc.NewElement("Component");
	p_parent->InsertEndChild(meshRenderer);
	meshRenderer->SetAttribute("type", "MeshRenderer");

	XMLElement* meshName = p_doc.NewElement("Model");
	meshRenderer->InsertEndChild(meshName);
	meshName->SetAttribute("name", m_model->Name().c_str());

	meshRenderer->InsertEndChild(meshName);
	if (m_model->HasSubMeshes())
		meshName->SetAttribute("subMeshes", "true");
	else
		meshName->SetAttribute("subMeshes", "false");
}

void MeshRenderer::DeSerialize(TinyXML2::XMLElement* p_componentNode)
{
	std::string meshName = p_componentNode->FirstChildElement("Model")->Attribute("name");
	std::string subModules = p_componentNode->FirstChildElement("Model")->Attribute("subMeshes");

	SetModel(Cloud::Get().ResourceManager<Rendering::Model>()->GetResource(meshName));
	if (subModules == "true")
		m_model->SetHasSubMeshes(true);
	else
		m_model->SetHasSubMeshes(false);
}

void MeshRenderer::SetModel(std::shared_ptr<Rendering::Model> p_model)
{
	m_model = p_model;
}

std::shared_ptr<Rendering::Model> MeshRenderer::Model()
{
	return m_model;
}
