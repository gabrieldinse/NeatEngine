#pragma once

#include "Neat/Renderer/ShaderProgram.h"


namespace Neat
{
   class TextureShader : public ShaderProgram
   {
   public:
      using ShaderProgram::ShaderProgram;

      void setTextures(Int* values, Int count)
      {
         bind();
         m_uniformTextures.set(values, count);
      }

      void setviewProjection(const Matrix4& viewProjection)
      {
         bind();
         m_uniformViewProjection.set(viewProjection);
      }

   private:
      Uniform<ShaderDataType::IntArray> m_uniformTextures{
         "u_textures[0]", getUniformLibrary()};
      Uniform<ShaderDataType::Matrix4> m_uniformViewProjection{
         "u_viewProjection", getUniformLibrary()};
   };
}