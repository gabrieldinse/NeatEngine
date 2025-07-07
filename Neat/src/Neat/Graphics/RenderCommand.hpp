#pragma once

#include <memory>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Graphics/RendererAPI.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class RenderCommand {
 public:
  static void init() { s_rendererAPI->init(); }

  static void setClearColor(const Vector4F color) {
    s_rendererAPI->setClearColor(color);
  }
  static void clear() { s_rendererAPI->clear(); }
  static void clearWithColor(const Vector4F color) {
    s_rendererAPI->clearWithColor(color);
  }

  static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray,
                          UInt32 indexCount = 0) {
    s_rendererAPI->drawIndexed(vertexArray, indexCount);
  }

  static void setViewport(UInt32 xOffset, UInt32 yOffset, UInt32 width,
                          UInt32 height) {
    s_rendererAPI->setViewport(xOffset, yOffset, width, height);
  }

 private:
  static std::unique_ptr<RendererAPI> s_rendererAPI;
};
}  // namespace Neat