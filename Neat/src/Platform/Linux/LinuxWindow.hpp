#pragma once

#include "Neat/Core/Window.hpp"

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
  GLFWwindow *m_glfwWindow;
  WindowProps m_windowProps;
  static Int32 s_windowCount;
};
}  // namespace Neat