#pragma once

#include "Neat/Graphics/ShaderProgram.hpp"


namespace Neat
{
   class TextureShader : public ShaderProgram
   {
   public:
      using ShaderProgram::ShaderProgram;

      void setTextures(Int32* values, Int32 count)
      {
         use();
         m_uniformTextures.set(values, count);
      }

      void setCameraTransform(const Matrix4F& projectionView)
      {
         use();
         m_cameraTransform.set(projectionView);
      }

   private:
      Uniform<ShaderDataType::IntArray> m_uniformTextures{
         getUniform<ShaderDataType::IntArray>("u_textures[0]")
      };
      Uniform<ShaderDataType::Matrix4F> m_cameraTransform{
         getUniform<ShaderDataType::Matrix4F>("u_cameraTransform")
      };
   };
}