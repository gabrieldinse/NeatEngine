#include "Neat/Graphics/ShaderDataType.hpp"
#include "Neat/Core/Log.hpp"

#include <glad/glad.h>


namespace Neat
{
   UInt32 OpenGLTypeConverter::sizeInBytes(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return 4;
         case ShaderDataType::Vector2F:    return 4 * 2;
         case ShaderDataType::Vector3F:    return 4 * 3;
         case ShaderDataType::Vector4F:    return 4 * 4;
         case ShaderDataType::Matrix3F:    return 4 * 3 * 3;
         case ShaderDataType::Matrix4F:    return 4 * 4 * 4;
         case ShaderDataType::Int:      return 4;
         case ShaderDataType::Vector2I:   return 4 * 2;
         case ShaderDataType::Vector3I:   return 4 * 3;
         case ShaderDataType::Vector4I:   return 4 * 4;
         case ShaderDataType::Bool:       return 4;
      }

      NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
      return 0;
   }

   UInt32 OpenGLTypeConverter::componentCount(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return 1;
         case ShaderDataType::Vector2F:    return 2;
         case ShaderDataType::Vector3F:    return 3;
         case ShaderDataType::Vector4F:    return 4;
         case ShaderDataType::Matrix3F:    return 3 * 3;
         case ShaderDataType::Matrix4F:    return 4 * 4;
         case ShaderDataType::Int:        return 1;
         case ShaderDataType::Vector2I:   return 2;
         case ShaderDataType::Vector3I:   return 3;
         case ShaderDataType::Vector4I:   return 4;
         case ShaderDataType::Bool:       return 1;
      }

      NT_CORE_ASSERT(false, "Unkown ShaderDataType!");
      return 0;
   }

   UInt32 OpenGLTypeConverter::baseType(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return GL_FLOAT;
         case ShaderDataType::Vector2F:    return GL_FLOAT;
         case ShaderDataType::Vector3F:    return GL_FLOAT;
         case ShaderDataType::Vector4F:    return GL_FLOAT;
         case ShaderDataType::Matrix3F:    return GL_FLOAT;
         case ShaderDataType::Matrix4F:    return GL_FLOAT;
         case ShaderDataType::Int:        return GL_INT;
         case ShaderDataType::Vector2I:   return GL_INT;
         case ShaderDataType::Vector3I:   return GL_INT;
         case ShaderDataType::Vector4I:   return GL_INT;
         case ShaderDataType::Bool:       return GL_BOOL;
      }

      NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }

   UInt32 OpenGLTypeConverter::type(ShaderDataType type)
   {
      switch (type)
      {
         case ShaderDataType::Float:      return GL_FLOAT;
         case ShaderDataType::Vector2F:    return GL_FLOAT_VEC2;
         case ShaderDataType::Vector3F:    return GL_FLOAT_VEC3;
         case ShaderDataType::Vector4F:    return GL_FLOAT_VEC4;
         case ShaderDataType::Matrix3F:    return GL_FLOAT_MAT3;
         case ShaderDataType::Matrix4F:    return GL_FLOAT_MAT4;
         case ShaderDataType::Int:      return GL_INT;
         case ShaderDataType::Vector2I:   return GL_INT_VEC2;
         case ShaderDataType::Vector3I:   return GL_INT_VEC3;
         case ShaderDataType::Vector4I:   return GL_INT_VEC4;
         case ShaderDataType::Bool:       return GL_BOOL;
      }

      NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }

   ShaderDataType OpenGLTypeConverter::toShaderDataType(UInt32 type, UInt32 count)
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
               return ShaderDataType::Vector2F;
            break;
         }

         case GL_FLOAT_VEC3:
         {
            if (count == 1)
               return ShaderDataType::Vector3F;
            break;
         }

         case GL_FLOAT_VEC4:
         {
            if (count == 1)
               return ShaderDataType::Vector4F;
            break;
         }

         case GL_FLOAT_MAT3:
         {
            if (count == 1)
               return ShaderDataType::Matrix3F;
            break;
         }

         case GL_FLOAT_MAT4:
         {
            if (count == 1)
               return ShaderDataType::Matrix4F;
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

   UInt32 OpenGLTypeConverter::fromStringToShaderType(
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