#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Neat {
void OpenGLRendererAPI::init() {
  NT_PROFILE_FUNCTION();
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::setClearColor(const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::clear() {
  NT_PROFILE_FUNCTION();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::clearWithColor(const Vector4F &color) {
  NT_PROFILE_FUNCTION();
  static constexpr float one = 1.0f;
  glClearBufferfv(GL_DEPTH, 0, &one);
  glClearBufferfv(GL_COLOR, 0, color.dataPointer());
}

void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray> &vertexArray,
                                    UInt32 indexCount) {
  NT_PROFILE_FUNCTION();
  UInt32 count = (indexCount == 0) ? vertexArray->getIndexBuffer()->getCount()
                                   : indexCount;
  vertexArray->bind();
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::setViewport(UInt32 xOffset, UInt32 yOffset,
                                    UInt32 width, UInt32 height) {
  NT_PROFILE_FUNCTION();
  glViewport(xOffset, yOffset, width, height);
}
}  // namespace Neat