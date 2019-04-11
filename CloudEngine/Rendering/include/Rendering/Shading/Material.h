#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "Rendering/Shading/Shader.h"
#include <Tools.h>

namespace Rendering
{
	class RENDERING_API Material
	{
	public:
		Material();
		Material(Shader* p_shader);
		~Material();

		void SetShader(Shader* p_shader);

		void ConfigureSlot(std::string p_slotName, int p_slotIndex);
		void SetTextureToSlot(Uniform* p_uniform, Texture* p_texture);

		Uniform* GetTextureSlotByName(std::string p_name);

		void DisplaySlots();

		std::vector<std::pair<Uniform*, Texture*>>& Slots();
		void AddSlot(std::pair<Uniform*, Texture*> p_sampler);

		void Bind();
		void UnBind();

		Shader* GetShader();

	private:
		void LoadSamplers();
		void ClearSlots();
		void OnReloadShader(Shader* p_shader);
		unsigned int numSlots = 0;

	private:
		Shader* m_shader = nullptr;
		std::vector<std::pair<Uniform*, Texture*>> m_slots;

		uint16_t m_reloadListener = 0;
	};
}