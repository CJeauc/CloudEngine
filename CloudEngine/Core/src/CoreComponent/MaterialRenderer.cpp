#include <Core/stdafx.h>
#include <Core/CoreComponent/MaterialRenderer.h>
#include "Core/CoreComponent/MeshRenderer.h"
#include "Core/ECS/ECS.h"
#include "Core/CoreComponent/Transform.h"
#include <Core/Engine/Cloud.h>
#include <Core/Managers/ResourceManager.h>
#include <Core/CoreComponent/UniformRendering.h>

using namespace Core::Components;
using namespace TinyXML2;

MaterialRenderer::MaterialRenderer()
	: m_material{ nullptr}
{
}

MaterialRenderer::MaterialRenderer(std::shared_ptr<Rendering::Material> p_material)
	: m_material { p_material }
{
}

MaterialRenderer::~MaterialRenderer()
{
}

void MaterialRenderer::SetMaterial(std::shared_ptr<Rendering::Material> p_material)
{
	m_material = p_material;
}

Rendering::Material& MaterialRenderer::Material()
{
	return *m_material;
}

std::shared_ptr<Rendering::Material> MaterialRenderer::MaterialSP()
{
	return m_material;
}

void MaterialRenderer::Serialize(TinyXML2::XMLDocument& p_doc, TinyXML2::XMLNode * p_parent) const
{
	XMLElement* materialRenderer = p_doc.NewElement("Component");
	p_parent->InsertEndChild(materialRenderer);
	materialRenderer->SetAttribute("type", "MaterialRenderer");

	XMLElement* shader = p_doc.NewElement("Shader");
	materialRenderer->InsertEndChild(shader);
	shader->SetAttribute("name", m_material->GetShader()->Name().c_str());

	XMLElement* textureSlots = p_doc.NewElement("TextureSlots");
	materialRenderer->InsertEndChild(textureSlots);

	for (auto slot : m_material->Slots())
	{
		textureSlots->SetAttribute(slot.first->Name.c_str(), slot.second->Name().c_str());
	}
}

void MaterialRenderer::DeSerialize(TinyXML2::XMLElement * p_componentNode)
{
	m_material->GetShader()->QueryUniformsAndAttributes();

	//Slots
	XMLElement* textureSlots = p_componentNode->FirstChildElement("TextureSlots");

	XMLAttribute* attribute = textureSlots->FirstAttribute();

	while (attribute)
	{
		Rendering::Texture* texture = Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource(attribute->Value()).get();

		m_material->SetTextureToSlot(m_material->GetTextureSlotByName(attribute->Name()), texture);
		attribute = attribute->Next();
	}
}

void MaterialRenderer::Init()
{
	auto owner = ECS::Get().m_entityManager->GetEntity(m_ownerId);

	owner->AddComponent<Transform>();

	owner->AddComponent<MeshRenderer>();
}
