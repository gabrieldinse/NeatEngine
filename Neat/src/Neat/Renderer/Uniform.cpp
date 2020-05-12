#include "Neat/Renderer/Uniform.h"

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
	UniformLibrary::UniformLibrary(UInt shaderProgramID)
		: shaderProgramID(shaderProgramID)
	{
		GLint uniform_count;
		GLint uniform_name_length;

		glGetProgramiv(
			this->shaderProgramID, GL_ACTIVE_UNIFORMS, &uniform_count);
		glGetProgramiv(
			this->shaderProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH,
			&uniform_name_length);
		std::vector<Char> name_data(uniform_name_length);

		for (GLint i = 0; i < uniform_count; i++)
		{
			GLenum type;
			GLint size;

			glGetActiveUniform(
				this->shaderProgramID, i, uniform_name_length, NULL, &size, &type,
				&name_data[0]);

			std::string name(&name_data[0]);

			auto location = glGetUniformLocation(
				this->shaderProgramID, name.c_str());

			NT_CORE_ASSERT(location != -1, "Uniform does not exist!");

			uniforms[std::string(name)] = std::make_unique<UniformData>(
				name, type, size, location);
		}
	}

	UniformLibrary::~UniformLibrary()
	{
	}

	Bool UniformLibrary::exists(const std::string& name) const
	{
		return (this->uniforms.find(name) != this->uniforms.end());
	}

	UniformData& UniformLibrary::operator[](const std::string& name)
	{
		return *this->uniforms.at(name);
	}

	const UniformData& UniformLibrary::operator[](const std::string& name) const
	{
		return *this->uniforms.at(name);
	}


	// ---------------------------------------------------------------------- //
	// UniformBase ---------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	UniformBase::~UniformBase()
	{
	}

	const std::string& UniformBase::getName() const
	{
		return this->data->name;
	}
	Int UniformBase::getType() const
	{
		return this->data->type;
	}
	Int UniformBase::getSize() const
	{
		return this->data->size;
	}
	Int UniformBase::getLocation() const
	{
		return this->data->location;
	}

	void UniformBase::checkUniform(ShaderDataType uniformType,
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		NT_CORE_ASSERT(uniformLibrary.exists(name), "Uniform was not found!");
		auto uniform_data = uniformLibrary[name];

		if (uniformType != openGLTypeToShaderDataType(
			uniform_data.type, uniform_data.size))
			NT_CORE_ASSERT(false, "Wrong Uniform type!");
	}

	// ---------------------------------------------------------------------- //
	// Uniform -------------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	Uniform<ShaderDataType::Float>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Vec2, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vec2>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Vec2, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vec3>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Vec3, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Vec4>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Vec4, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Int>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Int, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::IntArray>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::IntArray, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Mat3>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Mat3, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	Uniform<ShaderDataType::Mat4>::Uniform(
		const std::string& name, const UniformLibrary& uniformLibrary)
	{
		this->checkUniform(ShaderDataType::Mat4, name, uniformLibrary);
		this->data = std::make_unique<UniformData>(uniformLibrary[name]);
	}

	void Uniform<ShaderDataType::Float>::set(Float value)
   {
      glUniform1f(this->data->location, value);
   }

   void Uniform<ShaderDataType::Vec2>::set(Vec2 values)
   {
      glUniform2f(this->data->location, values.x, values.y);
   }

   void Uniform<ShaderDataType::Vec3>::set(Vec3 values)
   {
      glUniform3f(this->data->location, values.x, values.y, values.z);
   }

   void Uniform<ShaderDataType::Vec4>::set(Vec4 values)
   {
      glUniform4f(
			this->data->location, values.x, values.y, values.z, values.w);
   }

   void Uniform<ShaderDataType::Int>::set(Int value)
   {
      glUniform1i(this->data->location, value);
   }

   void Uniform<ShaderDataType::IntArray>::set(Int* values, Int count)
   {
      glUniform1iv(this->data->location, count, values);
   }

   void Uniform<ShaderDataType::Mat3>::set(Mat3 matrix)
   {
      glUniformMatrix3fv(
			this->data->location, 1, GL_TRUE, matrix.dataPointer());
   }

   void Uniform<ShaderDataType::Mat4>::set(Mat4 matrix)
   {
      glUniformMatrix4fv(
			this->data->location, 1, GL_TRUE, matrix.dataPointer());
   }
}