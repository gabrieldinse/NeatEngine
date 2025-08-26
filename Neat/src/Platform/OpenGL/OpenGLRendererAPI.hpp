#pragma once

#include "Neat/Graphics/RendererAPI.hpp"

namespace Neat {
class OpenGLRendererAPI : public RendererAPI {
 public:
  virtual void initialize() override;

  virtual void setClearColor(const Vector4F &color) override;
  virtual void clear() override;
  virtual void clearWithColor(const Vector4F &color) override;

  virtual void drawIndexed(const Ref<VertexArray> &vertexArray,
                           UInt32 indexCount = 0) override;

  virtual void setViewport(UInt32 xOffset, UInt32 yOffset, UInt32 width,
                           UInt32 height) override;
};
}  // namespace Neat