#pragma once

#include "Neat/Graphics/ShaderProgram.h"


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

      void setProjectionViewMatrix(const Matrix4& projectionView)
      {
         bind();
         m_uniformViewProjection.set(projectionView);
      }

   private:
      Uniform<ShaderDataType::IntArray> m_uniformTextures{
         getUniform<ShaderDataType::IntArray>("u_textures[0]")
      };
      Uniform<ShaderDataType::Matrix4> m_uniformViewProjection{
         getUniform<ShaderDataType::Matrix4>("u_projectionView")
      };
   };
}