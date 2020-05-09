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
         this->bind();
         this->textures.set(values, count);
      }

      void setviewProjection(const Mat4& viewProjection)
      {
         this->bind();
         this->viewProjection.set(viewProjection);
      }

   private:
      Uniform<ShaderDataType::IntArray> textures = { "u_textures[0]", this->getUniformLibrary() };
      Uniform<ShaderDataType::Mat4> viewProjection = { "u_viewProjection", this->getUniformLibrary() };
   };
}