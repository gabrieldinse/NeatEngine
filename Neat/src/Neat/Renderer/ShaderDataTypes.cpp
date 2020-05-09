#include "Neat/Renderer/ShaderDataTypes.h"
#include "Neat/Core/Log.h"

#include <glad/glad.h>


namespace Neat
{
	UInt shaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Vec2:   return 4 * 2;
			case ShaderDataType::Vec3:   return 4 * 3;
			case ShaderDataType::Vec4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 4;
		}

		NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	UInt shaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Vec2:   return 2;
			case ShaderDataType::Vec3:   return 3;
			case ShaderDataType::Vec4:   return 4;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
		}

		NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	UInt shaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Vec2:   return GL_FLOAT;
			case ShaderDataType::Vec3:   return GL_FLOAT;
			case ShaderDataType::Vec4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	UInt shaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Vec2:   return GL_FLOAT_VEC2;
			case ShaderDataType::Vec3:   return GL_FLOAT_VEC3;
			case ShaderDataType::Vec4:   return GL_FLOAT_VEC4;
			case ShaderDataType::Mat3:     return GL_FLOAT_MAT3;
			case ShaderDataType::Mat4:     return GL_FLOAT_MAT4;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT_VEC2;
			case ShaderDataType::Int3:     return GL_INT_VEC3;
			case ShaderDataType::Int4:     return GL_INT_VEC4;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	ShaderDataType openGLTypeToShaderDataType(UInt type, Int count)
	{
		if (type == GL_FLOAT)       
			if (count == 1)
				return ShaderDataType::Float;

		if (type == GL_FLOAT_VEC2)
			if (count == 1)
				return ShaderDataType::Vec2;

		if (type == GL_FLOAT_VEC3) 
			if (count == 1)
				return ShaderDataType::Vec3;

		if (type == GL_FLOAT_VEC4)
			if (count == 1)
				return ShaderDataType::Vec4;

		if (type == GL_FLOAT_MAT3)
			if (count == 1)
				return ShaderDataType::Mat3;

		if (type == GL_FLOAT_MAT4)
			if (count == 1)
				return ShaderDataType::Mat4;

		if (type == GL_INT)
			if (count == 1)
				return ShaderDataType::Int;

		if (type == GL_SAMPLER_2D)
			if (count == 1)
				return ShaderDataType::Int;
			if (count > 1)
				return ShaderDataType::IntArray;

		NT_CORE_ASSERT(false, "Unknown uniform type!");
		return ShaderDataType::None;
	}
}