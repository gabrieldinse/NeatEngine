#pragma once

#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"

namespace Neat {
class Renderer {
 public:
  static void init();
  static void shutdown();

  // static void beginScene(OrthographicCamera& camera);
  // static void endScene();

  // static void submit(const Ref<ShaderProgram>& shader,
  //    const Ref<VertexArray>& vertexArray,
  //    const Matrix4F& transform = Matrix4F(1.0f));

  static void onWindowResize(UInt32 width, UInt32 height);

  static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

 private:
  struct SceneData {
    Matrix4F viewProjectionMatrix;
  };

 private:
  static Scope<SceneData> m_sceneData;
};
}  // namespace Neat