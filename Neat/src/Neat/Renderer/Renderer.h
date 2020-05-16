#pragma once

#include "Neat/Renderer/RenderCommand.h"
#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Renderer/ShaderProgram.h"


namespace Neat
{
   class Renderer
   {
   public:
      static void init();
      static void shutdown();

      //static void beginScene(OrthographicCamera& camera);
      //static void endScene();

      //static void submit(const std::shared_ptr<ShaderProgram>& shader,
      //   const std::shared_ptr<VertexArray>& vertexArray,
      //   const Mat4& transform = Mat4(1.0f));

      static void onWindowResize(UInt width, UInt height);

   private:
      struct SceneData
      {
         Mat4 viewProjectionMatrix;
      };

   private:
      static std::unique_ptr<SceneData> m_sceneData;
   };
}