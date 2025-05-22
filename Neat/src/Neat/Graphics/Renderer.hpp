#pragma once

#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"


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
      //   const Matrix4F& transform = Matrix4F(1.0f));

      static void onWindowResize(UInt32 width, UInt32 height);

   private:
      struct SceneData
      {
         Matrix4F viewProjectionMatrix;
      };

   private:
      static std::unique_ptr<SceneData> m_sceneData;
   };
}