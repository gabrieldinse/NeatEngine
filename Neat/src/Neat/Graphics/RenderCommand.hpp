#pragma once

#include <memory>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Graphics/RendererAPI.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Debug/Debug.hpp"

namespace Neat {
class RenderCommand {
 public:
  static void init() {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->init();
  }

  static void setClearColor(const Vector4F &color) {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->setClearColor(color);
  }
  static void clear() {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->clear();
  }
  static void clearWithColor(const Vector4F &color) {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->clearWithColor(color);
  }

  static void drawIndexed(const Ref<VertexArray> &vertexArray,
                          UInt32 indexCount = 0) {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->drawIndexed(vertexArray, indexCount);
  }

  static void setViewport(UInt32 xOffset, UInt32 yOffset, UInt32 width,
                          UInt32 height) {
    NT_PROFILE_FUNCTION();
    s_rendererAPI->setViewport(xOffset, yOffset, width, height);
  }

 private:
  static Scope<RendererAPI> s_rendererAPI;
};
}  // namespace Neat