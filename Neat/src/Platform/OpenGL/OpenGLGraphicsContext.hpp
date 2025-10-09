#pragma once

#include "Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Neat {
class OpenGLGraphicsContext : public GraphicsContext {
 public:
  OpenGLGraphicsContext(GLFWwindow *window);
  virtual ~OpenGLGraphicsContext() = default;

  virtual void initialize() override;
  virtual void update() override;

 private:
  GLFWwindow *m_glfwWindow;
};
}  // namespace Neat