#pragma once

#include "Rendering/stdafx.h"
#include "Rendering/RenderingAPI.h"
#include "Rendering/Shading/Texture.h"
#include "CloudMath.h"
#include <Tools.h>

namespace Rendering
{
	enum SHADER_TYPE
	{
		BOOL = GL_BOOL,
		INT = GL_INT,
		FLOAT = GL_FLOAT,
		SAMPLER1D = GL_SAMPLER_1D,
		SAMPLER2D = GL_SAMPLER_2D,
		SAMPLER3D = GL_SAMPLER_3D,
		SAMPLERCUBE = GL_SAMPLER_CUBE,
		VEC2 = GL_FLOAT_VEC2,
		VEC3 = GL_FLOAT_VEC3,
		VEC4 = GL_FLOAT_VEC4,
		MAT2 = GL_FLOAT_MAT2,
		MAT3 = GL_FLOAT_MAT3,
		MAT4 = GL_FLOAT_MAT4,
	};

	struct Uniform
	{
		SHADER_TYPE  Type;
		std::string  Name;
		int          Size;
		unsigned int Location;

		/*Uniform()
		{
			Type = SAMPLER2D;
		}*/
	};

	struct UniformValue
	{
		SHADER_TYPE Type;
		union
		{
			bool       Bool;
			int        Int;
			float      Float;

			CloudMath::Vector2f Vec2;
			CloudMath::Vector3f Vec3;
			CloudMath::Vector4f Vec4;
			CloudMath::Matrix2f Mat2;
			CloudMath::Matrix3f Mat3;
			CloudMath::Matrix4f Mat4;
		};
	};

	struct UniformValueSampler
	{
		SHADER_TYPE  Type;
		unsigned int Unit;
		union
		{
			Texture    *Texture;
		};
	};

	struct VertexAttribute
	{
		SHADER_TYPE  Type;
		std::string  Name;
		int          Size;
		unsigned int Location;
	};


	class Material;						//Forward Declaration

	class RENDERING_API Shader
	{
		friend class Material;

	public:
		Shader();
		Shader(std::pair<unsigned int, std::string> p_pair);
		Shader(const Shader& p_other) = delete;
		~Shader();

		Shader& operator = (const Shader& p_other) = delete;
		Shader& operator = (Shader&& p_other);

		void Bind() const;
		void UnBind() const;
		void DeleteProgram() const;

		void SetUniformMat4(const std::string& p_name,const CloudMath::Matrix4f& p_Matrix);
		void SetUniformInt(const std::string& p_name, int p_value);
		void SetUniformVec4(const std::string& p_name, const CloudMath::Vector4f& p_vec4);
		void SetUniformVec3(const std::string& p_name, const CloudMath::Vector3f& p_vec3);

		unsigned int ID() const;

		void QueryUniformsAndAttributes();

		std::string Name() { return m_name; };

		static Tools::Event<Shader*> GlobalReloadEvent;
		Tools::Event<Shader*> ReloadEvent;

	private:
		int GetUniformLocation(std::string p_name);

	private:
		unsigned int m_ID;
		std::string m_name;

		std::vector<Uniform>         m_uniforms;
		std::vector<VertexAttribute> m_attributes;
	};
}