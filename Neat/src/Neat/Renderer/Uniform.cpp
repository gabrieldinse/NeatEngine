#include "Neat/Renderer/Uniform.h"
#include "Neat/Renderer/ShaderProgram.h"

#include <glad/glad.h>


namespace Neat
{
	// ---------------------------------------------------------------------- //
	// UniformData ---------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	struct UniformData
	{
		UniformData(
			const std::string& name, Int type, Int size, Int location)
			: name(name)
			, type(type)
			, size(size)
			, location(location)
		{}
		
		UniformData() = default;

		std::string name;
		Int type;
		Int size;
		Int location;
	};


	// ---------------------------------------------------------------------- //
	// UniformLibrary-------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	UniformLibrary::UniformLibrary(ShaderProgram& shader)
		: m_shader(shader)
	{
		GLint uniform_count;
		GLint uniform_name_length;

		glGetProgramiv(
			m_shader.getId(), GL_ACTIVE_UNIFORMS, &uniform_count);
		glGetProgramiv(
			m_shader.getId(), GL_ACTIVE_UNIFORM_MAX_LENGTH,
			&uniform_name_length);
		std::vector<char> name_data(uniform_name_length);

		for (GLint i = 0; i < uniform_count; i++)
		{
			GLenum type;
			GLint size;

			glGetActiveUniform(
				m_shader.getId(), i, uniform_name_length, NULL, &size, &type,
				&name_data[0]);

			std::string name(&name_data[0]);

			auto location = glGetUniformLocation(
				m_shader.getId(), name.c_str());

			NT_CORE_ASSERT(location != -1, "Uniform does not exist!");

			uniforms[std::string(name)] = std::make_unique<UniformData>(
				name, type, size, location);
		}
	}

	UniformLibrary::~UniformLibrary()
	{
	}

	bool UniformLibrary::exists(const std::string& name) const
	{
		return (uniforms.find(name) != uniforms.end());
	}

	UniformData& UniformLibrary::operator[](const std::string& name)
	{
		return *uniforms.at(name);
	}

	const UniformData& UniformLibrary::operator[](const std::string& name) const
	{
		return *uniforms.at(name);
	}


	// ---------------------------------------------------------------------- //
	// UniformBase ---------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	UniformBase::~UniformBase()
	{
	}

	const std::string& UniformBase::getName() const
	{
		return m_data->name;
	}
	Int UniformBase::getType() const
	{
		return m_data->type;
	}
	Int UniformBase::getSize() const
	{
		return m_data->size;
	}
	Int UniformBase::getLocation() const
	{
		return m_data->location;
	}

	void UniformBase::checkUniform(ShaderDataType uniformType,
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		NT_CORE_ASSERT(uniformLibrary.exists(name), "Uniform was not found!");
		auto uniform_data = uniformLibrary[name];

		if (uniformType != OpenGLTypeConverter::toShaderDataType(
			uniform_data.type, uniform_data.size))
			NT_CORE_ASSERT(false, "Wrong Uniform type!");
	}

	// ---------------------------------------------------------------------- //
	// Uniform -------------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	Uniform<ShaderDataType::Float>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Float, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vector2>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Vector2, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vector3>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Vector3, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vector4>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Vector4, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Int>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Int, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::IntArray>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::IntArray, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Matrix3>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Matrix3, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Matrix4>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		checkUniform(ShaderDataType::Matrix4, name, uniformLibrary);
		m_data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	void Uniform<ShaderDataType::Float>::set(float value)
   {
      glUniform1f(m_data->location, value);
   }

   void Uniform<ShaderDataType::Vector2>::set(Vector2 values)
   {
      glUniform2f(m_data->location, values.x, values.y);
   }

   void Uniform<ShaderDataType::Vector3>::set(Vector3 values)
   {
      glUniform3f(m_data->location, values.x, values.y, values.z);
   }

   void Uniform<ShaderDataType::Vector4>::set(Vector4 values)
   {
      glUniform4f(
			m_data->location, values.x, values.y, values.z, values.w);
   }

   void Uniform<ShaderDataType::Int>::set(Int value)
   {
      glUniform1i(m_data->location, value);
   }

   void Uniform<ShaderDataType::IntArray>::set(Int* values, Int count)
   {
      glUniform1iv(m_data->location, count, values);
   }

   void Uniform<ShaderDataType::Matrix3>::set(Matrix3 matrix)
   {
      glUniformMatrix3fv(
			m_data->location, 1, GL_TRUE, matrix.dataPointer());
   }

   void Uniform<ShaderDataType::Matrix4>::set(Matrix4 matrix)
   {
      glUniformMatrix4fv(
			m_data->location, 1, GL_TRUE, matrix.dataPointer());
   }
}