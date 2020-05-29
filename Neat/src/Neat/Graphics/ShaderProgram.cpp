#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <cctype>
#include <filesystem>

#include "Neat/Core/Log.h"
#include "Neat/Graphics/ShaderProgram.h"
#include "Neat/Graphics/ShaderDataType.h"
#include "Neat/Math/MatrixOperations.h"

#include <glad/glad.h>


namespace Neat
{
	// ---------------------------------------------------------------------- //
	// ShaderProgramBuilder ------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	ShaderProgramBuilder::ShaderProgramBuilder(const std::string& filepath)
	{
		std::ifstream input(filepath, std::ios::in | std::ios::binary);

		if (input.is_open())
		{
			input.seekg(0, std::ios::end);
			m_fileContent.resize(input.tellg());
			input.seekg(0, std::ios::beg);
			input.read(&m_fileContent[0], m_fileContent.size());
			input.close();
		}
		else
		{
			NT_CORE_ERROR("Could not open file \"{0}\"", filepath);
			NT_CORE_ASSERT(false, "");
		}

		preprocessShaderSource();
	}

	ShaderProgramBuilder::ShaderProgramBuilder(const std::string& vertexSource,
		const std::string& fragmentSource)
		: m_shaderSources({
			{ GL_VERTEX_SHADER, vertexSource },
			{ GL_FRAGMENT_SHADER, fragmentSource } }
			) {}

	UInt ShaderProgramBuilder::build()
	{
		NT_CORE_ASSERT(m_shaderSources.size() <= 2,
			"The maximum number of supported shaders is 2.");

		UInt program_id = glCreateProgram();

		std::array<UInt, 2> shaders_id;
		Int shaders_id_index = 0;
		for (auto&& [type, shader_source] : m_shaderSources)
		{
			UInt shader_id = glCreateShader(type);

			const char* source = shader_source.c_str();
			glShaderSource(shader_id, 1, &source, 0);
			glCompileShader(shader_id);

			Int compiled = 0;
			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE)
			{
				Int max_length = 0;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<char> info_log(max_length);
				glGetShaderInfoLog(shader_id, max_length, &max_length,
					&info_log[0]);

				glDeleteShader(shader_id);

				NT_CORE_ERROR("{0}", info_log.data());
				NT_CORE_ASSERT(false, "ShaderProgram compilation failure.");

				return 0;
			}

			glAttachShader(program_id, shader_id);
			shaders_id[shaders_id_index++] = shader_id;
		}

		glLinkProgram(program_id);

		Int linked = 0;
		glGetProgramiv(program_id, GL_LINK_STATUS, (Int*)&linked);
		if (linked == GL_FALSE)
		{
			Int max_length = 0;
			glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<char> info_log(max_length);
			glGetProgramInfoLog(program_id, max_length, &max_length, &info_log[0]);

			glDeleteProgram(program_id);

			for (auto shader_id : shaders_id)
				glDeleteShader(shader_id);

			NT_CORE_ERROR("{0}", info_log.data());
			NT_CORE_ASSERT(false, "ShaderProgram program_id link failure.");

			return 0;
		}

		for (auto shader_id : shaders_id)
			glDetachShader(program_id, shader_id);

		return program_id;
	}

	void ShaderProgramBuilder::preprocessShaderSource()
	{
		const char* type_token = "#type";
		auto type_token_lenght = strlen(type_token);
		auto pos = m_fileContent.find(type_token, 0);

		while (pos != std::string::npos)
		{
			auto shader_type_begin = m_fileContent.find_first_not_of(
				" \t", pos + type_token_lenght);
			auto shader_type_end = m_fileContent.find_first_of(
				" \t\r\n", shader_type_begin);
			auto eol_pos = m_fileContent.find_first_of("\r\n", shader_type_end);

			NT_CORE_ASSERT(eol_pos != std::string::npos,
				"ShaderProgram source syntax error.");

			auto shader_type_name = m_fileContent.substr(
				shader_type_begin, shader_type_end - shader_type_begin);
			auto shader_type =
				OpenGLTypeConverter::fromStringToShaderType(shader_type_name);

			auto next_line_pos = m_fileContent.find_first_not_of("\r\n", eol_pos);
			pos = m_fileContent.find(type_token, next_line_pos);
			m_shaderSources[shader_type] =
				m_fileContent.substr(next_line_pos,
					(pos == std::string::npos ? pos : pos - next_line_pos));
		}
	}


	// ---------------------------------------------------------------------- //
	// ShaderProgram -------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	ShaderProgram::ShaderProgram(const std::string& filepath)
		: m_id(ShaderProgramBuilder(filepath).build())
		, m_uniformLibrary(*this)
		, m_name(std::filesystem::path(filepath).stem().string())
	{
	}

	ShaderProgram::ShaderProgram(const std::string& name,
		const std::string& filepath)
		: m_id(ShaderProgramBuilder(filepath).build())
		, m_uniformLibrary(*this)
		, m_name(name)
	{
	}

	ShaderProgram::ShaderProgram(
		const std::string& name,
		const std::string& vertexSource,
		const std::string& fragmentSource)
		: m_id(ShaderProgramBuilder(vertexSource, fragmentSource).build())
		, m_uniformLibrary(*this)
		, m_name(name)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(m_id);
	}

	void ShaderProgram::unbind() const
	{
		glUseProgram(0);
	}


	// -------------------------------------------------------------------------
	// ShaderLibrary -----------------------------------------------------------
	// -------------------------------------------------------------------------
	void ShaderLibrary::add(const std::shared_ptr<ShaderProgram>& shader)
	{
		auto& name = shader->getName();
		NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

		m_shaders[name] = shader;
	}

	void ShaderLibrary::add(const std::string& name,
		const std::shared_ptr<ShaderProgram>& shader)
	{
		NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

		shader->setName(name);
		m_shaders[name] = shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = std::make_shared<ShaderProgram>(filepath);
		add(shader);

		return shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::load(
		const std::string& name,
		const std::string& filepath)
	{
		auto shader = std::make_shared<ShaderProgram>(name, filepath);
		add(shader);

		return shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::get(const std::string& name)
	{
		NT_CORE_ASSERT(exists(name), "ShaderProgram not found!");

		return m_shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return (m_shaders.find(name) != m_shaders.end());
	}
}