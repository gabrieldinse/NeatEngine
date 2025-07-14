#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Neat {
void OpenGLRendererAPI::init() {
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::setClearColor(const Vector4F color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::clearWithColor(const Vector4F color) {
  static constexpr float one = 1.0f;
  glClearBufferfv(GL_DEPTH, 0, &one);
  glClearBufferfv(GL_COLOR, 0, color.dataPointer());
}

void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray> &vertexArray,
                                    UInt32 indexCount) {
  UInt32 count = (indexCount == 0) ? vertexArray->getIndexBuffer()->getCount()
                                   : indexCount;

  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRendererAPI::setViewport(UInt32 xOffset, UInt32 yOffset,
                                    UInt32 width, UInt32 height) {
  glViewport(xOffset, yOffset, width, height);
}
}  // namespace Neat