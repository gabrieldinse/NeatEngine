#include "Neat/Graphics/ShaderDataType.h"
#include "Neat/Core/Log.h"

#include <glad/glad.h>


namespace Neat
{
   UInt OpenGLTypeConverter::sizeInBytes(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return 4;
         case ShaderDataType::Vector2:    return 4 * 2;
         case ShaderDataType::Vector3:    return 4 * 3;
         case ShaderDataType::Vector4:    return 4 * 4;
         case ShaderDataType::Matrix3:    return 4 * 3 * 3;
         case ShaderDataType::Matrix4:    return 4 * 4 * 4;
         case ShaderDataType::Int:        return 4;
         case ShaderDataType::IVector2:   return 4 * 2;
         case ShaderDataType::IVector3:   return 4 * 3;
         case ShaderDataType::IVector4:   return 4 * 4;
         case ShaderDataType::Bool:       return 4;
      }

      NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
      return 0;
   }

   UInt OpenGLTypeConverter::componentCount(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:		return 1;
         case ShaderDataType::Vector2:		return 2;
         case ShaderDataType::Vector3:		return 3;
         case ShaderDataType::Vector4:		return 4;
         case ShaderDataType::Matrix3:		return 3 * 3;
         case ShaderDataType::Matrix4:		return 4 * 4;
         case ShaderDataType::Int:			return 1;
         case ShaderDataType::IVector2:	return 2;
         case ShaderDataType::IVector3:	return 3;
         case ShaderDataType::IVector4:	return 4;
         case ShaderDataType::Bool:			return 1;
      }

      NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
      return 0;
   }

   UInt OpenGLTypeConverter::baseType(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return GL_FLOAT;
         case ShaderDataType::Vector2:    return GL_FLOAT;
         case ShaderDataType::Vector3:    return GL_FLOAT;
         case ShaderDataType::Vector4:    return GL_FLOAT;
         case ShaderDataType::Matrix3:    return GL_FLOAT;
         case ShaderDataType::Matrix4:    return GL_FLOAT;
         case ShaderDataType::Int:        return GL_INT;
         case ShaderDataType::IVector2:   return GL_INT;
         case ShaderDataType::IVector3:   return GL_INT;
         case ShaderDataType::IVector4:   return GL_INT;
         case ShaderDataType::Bool:       return GL_BOOL;
      }

      NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }

   UInt OpenGLTypeConverter::type(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return GL_FLOAT;
         case ShaderDataType::Vector2:    return GL_FLOAT_VEC2;
         case ShaderDataType::Vector3:    return GL_FLOAT_VEC3;
         case ShaderDataType::Vector4:    return GL_FLOAT_VEC4;
         case ShaderDataType::Matrix3:    return GL_FLOAT_MAT3;
         case ShaderDataType::Matrix4:    return GL_FLOAT_MAT4;
         case ShaderDataType::Int:        return GL_INT;
         case ShaderDataType::IVector2:   return GL_INT_VEC2;
         case ShaderDataType::IVector3:   return GL_INT_VEC3;
         case ShaderDataType::IVector4:   return GL_INT_VEC4;
         case ShaderDataType::Bool:       return GL_BOOL;
      }

      NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }

   ShaderDataType OpenGLTypeConverter::toShaderDataType(UInt type, Int count)
   {
      switch (type)
      {
         case GL_FLOAT:
         {
            if (count == 1)
               return ShaderDataType::Float;
            break;
         }

         case GL_FLOAT_VEC2:
         {
            if (count == 1)
               return ShaderDataType::Vector2;
            break;
         }

         case GL_FLOAT_VEC3:
         {
            if (count == 1)
               return ShaderDataType::Vector3;
            break;
         }

         case GL_FLOAT_VEC4:
         {
            if (count == 1)
               return ShaderDataType::Vector4;
            break;
         }

         case GL_FLOAT_MAT3:
         {
            if (count == 1)
               return ShaderDataType::Matrix3;
            break;
         }

         case GL_FLOAT_MAT4:
         {
            if (count == 1)
               return ShaderDataType::Matrix4;
            break;
         }

         case GL_INT:
         {
            if (count == 1)
               return ShaderDataType::Int;
            break;
         }

         case GL_SAMPLER_2D:
         {
            if (count == 1)
               return ShaderDataType::Int;
            if (count > 1)
               return ShaderDataType::IntArray;
            break;
         }
      }

      NT_CORE_ASSERT(false, "Unknown uniform type!");
      return ShaderDataType::None;
   }

   UInt OpenGLTypeConverter::fromStringToShaderType(
      const std::string& type)
   {
      if (type == "vertex")
         return GL_VERTEX_SHADER;

      if (type == "fragment" || type == "pixel")
         return GL_FRAGMENT_SHADER;

      NT_CORE_ASSERT(false, "Unkown shader type.");
      return 0;
   }
}