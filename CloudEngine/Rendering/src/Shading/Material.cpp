#include "Rendering/stdafx.h"
#include "Rendering/Shading/Material.h"

using namespace Rendering;

Material::Material()
{
	//Rendering::Shader::ReloadEvent += BIND(&Material::OnReloadShader, this, HOLDER_1);
}

Material::Material(Shader* p_shader)
{
	SetShader(p_shader);

	m_slots.clear();
	LoadSamplers();
}

Material::~Material()
{
}

void Material::SetShader(Shader* p_shader)
{
	if (m_shader)
		m_shader->ReloadEvent -= m_reloadListener;

	m_shader = p_shader;

	m_reloadListener = m_shader->ReloadEvent += BIND(&Material::OnReloadShader, this, HOLDER_1);
	
	m_slots.clear();
	LoadSamplers();
}

void Material::ConfigureSlot(std::string p_slotName, int p_slotIndex)
{
	m_shader->Bind();
	m_shader->SetUniformInt(p_slotName, p_slotIndex);
	m_shader->UnBind();
}

void Material::SetTextureToSlot(Uniform* p_uniform, Texture* p_texture)
{
	for (unsigned int i = 0; i < m_slots.size(); ++i)
	{
		if (m_slots[i].first == p_uniform)
		{
			m_slots[i].second = p_texture;
			return;
		}
	}

	LOG(Log::Error(), "We Have a problem Set Texture To slot");
}

Uniform* Material::GetTextureSlotByName(std::string p_name)
{
	for (unsigned int i = 0; i < m_slots.size(); ++i)
	{
		if (m_slots[i].first->Name == p_name)
		{
			return m_slots[i].first;
		}
	}

	LOG(Log::Error(), "We Have a problem get slot by name");
	return m_slots[0].first;
}

void Material::DisplaySlots()
{
	for (unsigned int i = 0; i < m_slots.size(); ++i)
	{
		SLOG(Log::Info(), m_slots[i].first->Name << " " << m_slots[i].second->Name());
	}
}

std::vector<std::pair<Uniform*, Texture*>>& Material::Slots()
{
	return m_slots;
}

void Material::AddSlot(std::pair<Uniform*, Texture*> p_sampler)
{
	m_slots.push_back(p_sampler);
}

void Material::Bind()
{
	m_shader->Bind();

	for (unsigned int i = 0; i < m_slots.size(); ++i)
	{
		if (m_slots[i].second != nullptr)
		{
			m_slots[i].second->Bind(i);
		}
		else
		{
			LOG(Log::Warning(), " Texture Slot Not Configured " << m_slots[i].first->Name << " Shader:" << m_shader->Name());
		}
	}
}

void Material::UnBind()
{
	m_shader->UnBind();
}

Shader* Material::GetShader()
{
	return m_shader;
}

void Material::LoadSamplers()
{
	unsigned int unit = 0;
	m_shader->Bind();

	for (unsigned int i = 0; i < m_shader->m_uniforms.size(); ++i)
	{
		if (m_shader->m_uniforms[i].Type == SHADER_TYPE::SAMPLER2D)
		{
			m_shader->SetUniformInt(m_shader->m_uniforms[i].Name, unit);
			m_slots.push_back(std::pair(&m_shader->m_uniforms[i], nullptr));
			++unit;
		}
	}
	numSlots = m_slots.size();
	m_shader->UnBind();
}

void Rendering::Material::ClearSlots()
{
	m_slots.clear();
}

void Material::OnReloadShader(Shader* p_shader)
{
	//When we Reload a Shader we keep the old configured texture slots
	std::vector<Texture*> oldTextures;
	for (auto slot : m_slots)
		oldTextures.push_back(slot.second);

	m_slots.clear();
	LoadSamplers();

	unsigned int slotsCounter = 0;

	for (auto& slot : m_slots)
	{
		if (slotsCounter > oldTextures.size())
			break;

		slot.second = oldTextures.at(slotsCounter);

		++slotsCounter;
	}
}
