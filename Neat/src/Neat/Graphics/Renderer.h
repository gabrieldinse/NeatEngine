#pragma once

#include "Neat/Graphics/RenderCommand.h"
#include "Neat/Graphics/Camera.h"
#include "Neat/Graphics/ShaderProgram.h"


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
      //   const Matrix4& transform = Matrix4(1.0f));

      static void onWindowResize(UInt32 width, UInt32 height);

   private:
      struct SceneData
      {
         Matrix4 viewProjectionMatrix;
      };

   private:
      static std::unique_ptr<SceneData> m_sceneData;
   };
}