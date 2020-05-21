#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <cctype>
#include <filesystem>

#include "Neat/Core/Log.h"
#include "Neat/Renderer/ShaderProgram.h"
#include "Neat/Renderer/ShaderDataTypes.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{


	std::string readFile(const std::string& filepath)
	{
		NT_PROFILE_FUNCTION();

		std::string file_content;
		std::ifstream input(filepath, std::ios::in | std::ios::binary);
		if (input)
		{
			input.seekg(0, std::ios::end);
			file_content.resize(input.tellg());
			input.seekg(0, std::ios::beg);
			input.read(&file_content[0], file_content.size());
			input.close();
		}
		else
		{
			NT_CORE_ERROR("Could not open file \"{0}\"", filepath);
		}

		return file_content;
	}

	std::unordered_map<UInt, std::string> preprocessShaderSource(
		const std::string& source)
	{
		NT_PROFILE_FUNCTION();

		std::unordered_map<UInt, std::string> shader_sources;
		const char* type_token = "#type";
		auto type_token_lenght = strlen(type_token);
		auto pos = source.find(type_token, 0);
		while (pos != std::string::npos)
		{
			auto shader_type_begin = source.find_first_not_of(
				" \t", pos + type_token_lenght);
			auto shader_type_end = source.find_first_of(
				" \t\r\n", shader_type_begin);
			auto eol_pos = source.find_first_of("\r\n", shader_type_end);

			NT_CORE_ASSERT(eol_pos != std::string::npos,
				"ShaderProgram source syntax error.");

			auto shader_type = source.substr(
				shader_type_begin, shader_type_end - shader_type_begin);
			auto gl_type = stringToOpenGLShaderType(shader_type);

			auto next_line_pos = source.find_first_not_of("\r\n", eol_pos);
			pos = source.find(type_token, next_line_pos);
			shader_sources[gl_type] =
				source.substr(next_line_pos,
					(pos == std::string::npos ? pos : pos - next_line_pos));
		}

		return shader_sources;
	}


	// ---------------------------------------------------------------------- //
	// ShaderProgram -------------------------------------------------------- //
	// ---------------------------------------------------------------------- //
	ShaderProgram::ShaderProgram(const std::string& filepath)
	{
		NT_PROFILE_FUNCTION();

		auto source = readFile(filepath);
		auto shader_sources = preprocessShaderSource(source);
		compile(shader_sources);
		m_name = std::filesystem::path(filepath).stem().string();
		m_uniformLibrary = std::make_unique<UniformLibrary>(m_id);
	}

	ShaderProgram::ShaderProgram(const std::string& name,
		const std::string& filepath)
	{
		NT_PROFILE_FUNCTION();

		auto source = readFile(filepath);
		auto shader_sources = preprocessShaderSource(source);
		compile(shader_sources);
		m_name = name;
		m_uniformLibrary = std::make_unique<UniformLibrary>(m_id);
	}

	ShaderProgram::ShaderProgram(
		const std::string& name,
		const std::string& vertexSource,
		const std::string& fragmentSource)
	{
		NT_PROFILE_FUNCTION();

		std::unordered_map<UInt, std::string> shader_sources;
		shader_sources[GL_VERTEX_SHADER] = vertexSource;
		shader_sources[GL_FRAGMENT_SHADER] = fragmentSource;
		compile(shader_sources);
		m_uniformLibrary = std::make_unique<UniformLibrary>(m_id);
	}

	ShaderProgram::~ShaderProgram()
	{
		NT_PROFILE_FUNCTION();

		glDeleteProgram(m_id);
	}

	void ShaderProgram::compile(const std::unordered_map<UInt,
		std::string>& shaderSources)
	{
		NT_PROFILE_FUNCTION();

		NT_CORE_ASSERT(shaderSources.size() <= 2,
			"The maximum number of supported shaders is 2.");

		auto program_id = glCreateProgram();

		std::array<UInt, 2> shaders_id;
		Int shaders_id_index = 0;
		for (auto& shader_info : shaderSources)
		{
			auto type = shader_info.first;
			const auto& shader_source = shader_info.second;

			UInt shader_id = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
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
				glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

				glDeleteShader(shader_id);

				NT_CORE_ERROR("{0}", info_log.data());
				NT_CORE_ASSERT(false, "ShaderProgram compilation failure.");
				return;
			}

			glAttachShader(program_id, shader_id);
			shaders_id[shaders_id_index++] = shader_id;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together
		glLinkProgram(program_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
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
			return;
		}

		// Always onDetach shaders after a successful link
		for (auto shader_id : shaders_id)
			glDetachShader(program_id, shader_id);

		m_id = program_id;
	}

	void ShaderProgram::bind() const
	{
		NT_PROFILE_FUNCTION();

		glUseProgram(m_id);
	}

	void ShaderProgram::unbind() const
	{
		NT_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	// -------------------------------------------------------------------------
	// ShaderLibrary -----------------------------------------------------------
	// -------------------------------------------------------------------------
	void ShaderLibrary::add(const std::shared_ptr<ShaderProgram>& shader)
	{
		NT_PROFILE_FUNCTION();

		auto& name = shader->getName();
		NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");
		m_shaders[name] = shader;
	}

	void ShaderLibrary::add(const std::string& name, const std::shared_ptr<ShaderProgram>& shader)
	{
		NT_PROFILE_FUNCTION();

		NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");
		shader->setName(name);
		m_shaders[name] = shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::load(const std::string& filepath)
	{
		NT_PROFILE_FUNCTION();

		auto shader = std::make_shared<ShaderProgram>(filepath);
		add(shader);

		return shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::load(
		const std::string& name,
		const std::string& filepath)
	{
		NT_PROFILE_FUNCTION();

		auto shader = std::make_shared<ShaderProgram>(name, filepath);
		add(shader);

		return shader;
	}

	std::shared_ptr<ShaderProgram> ShaderLibrary::get(const std::string& name)
	{
		NT_PROFILE_FUNCTION();

		NT_CORE_ASSERT(exists(name), "ShaderProgram not found!");

		return m_shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		NT_PROFILE_FUNCTION();

		return (m_shaders.find(name) != m_shaders.end());
	}

}