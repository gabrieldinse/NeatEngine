#pragma once

#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"

namespace Neat {
class Renderer {
 public:
  static void initialize();
  static void shutdown();

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