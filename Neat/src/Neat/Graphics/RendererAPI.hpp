#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class RendererAPI {
 public:
  enum class API {
    None = 0,
    OpenGL = 1,
  };

 public:
  virtual ~RendererAPI() = default;

  virtual void initialize() = 0;

  virtual void setClearColor(const Vector4F &color) = 0;
  virtual void clear() = 0;
  virtual void clearWithColor(const Vector4F &color) = 0;

  virtual void drawIndexed(const Ref<VertexArray> &vertexArray,
                           UInt32 indexCount = 0) = 0;

  virtual void setViewport(UInt32 xOffset, UInt32 yOffset, UInt32 width,
                           UInt32 height) = 0;

  static API getAPI() { return s_api; }
  static Scope<RendererAPI> create();

 private:
  static API s_api;
};
}  // namespace Neat