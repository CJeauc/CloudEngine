#include "Rendering/stdafx.h"
#include "Rendering/Shading/UniformBuffer.h"

using namespace Rendering;

UniformBuffer::UniformBuffer()
{
}

void UniformBuffer::Create(unsigned int p_size)
{
	glGenBuffers(1, &m_uboID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboID);
	glBufferData(GL_UNIFORM_BUFFER, p_size, NULL, GL_STATIC_DRAW); // allocate memory
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::UpdateData(unsigned int p_offset, unsigned int p_size, void* p_data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboID);

	glBufferSubData(GL_UNIFORM_BUFFER, p_offset, p_size, p_data);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::BindShader(unsigned int p_shaderID, const std::string& p_name, unsigned int p_slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, p_slot, m_uboID);

	unsigned int blockIndex = glGetUniformBlockIndex(p_shaderID, p_name.c_str());
	if (blockIndex < 0)
		SLOG(Log::Warning(), "Oups");
	glUniformBlockBinding(p_shaderID, blockIndex, p_slot);
}