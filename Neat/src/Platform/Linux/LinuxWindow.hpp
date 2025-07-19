#pragma once

#include "Neat/Core/Window.hpp"
#include "Neat/Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Neat {

class LinuxWindow : public Window {
 public:
  LinuxWindow(const WindowProps &props);
  virtual ~LinuxWindow();

  virtual void onUpdate() override;

  virtual Int32 getWidth() const override;
  virtual Int32 getHeight() const override;
  virtual float getAspectRatio() const override;

  virtual void *getNativeWindow() const override;

  virtual bool isMinimized() const override;

  virtual void setVSync(bool enabled) override;
  virtual bool isVSync() const override;

 private:
  WindowProps m_windowProps;
  Scope<GraphicsContext> m_graphicsContext;
  GLFWwindow *m_glfwWindow = nullptr;
  static Int32 s_windowCount;
};
}  // namespace Neat