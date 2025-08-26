#include "NeatPCH.hpp"

#include "Neat/Graphics/Renderer.hpp"
#include "Neat/Graphics/Renderer2D.hpp"

namespace Neat {
Scope<Renderer::SceneData> Renderer::m_sceneData =
    makeScope<Renderer::SceneData>();

void Renderer::initialize() {
  NT_PROFILE_FUNCTION();
  RenderCommand::initialize();
  Renderer2D::initialize();
}

void Renderer::shutdown() {
  NT_PROFILE_FUNCTION();
  Renderer2D::shutdown();
}

void Renderer::onWindowResize(UInt32 width, UInt32 height) {
  NT_PROFILE_FUNCTION();
  RenderCommand::setViewport(0, 0, width, height);
}
}  // namespace Neat