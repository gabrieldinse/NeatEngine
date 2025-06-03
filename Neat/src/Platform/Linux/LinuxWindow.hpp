#pragma once

#include "Neat/Core/Window.hpp"

struct GLFWwindow;

namespace Neat {
struct GLFWwindowDeleter {
  void operator()(GLFWwindow *ptr);
};
using GLFWwindowUniquePtr = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

class LinuxWindow : public Window {
 public:
  LinuxWindow(const WindowProps &props);
  virtual ~LinuxWindow() = default;

  virtual void onUpdate() override;

  virtual Int32 getWidth() const override;
  virtual Int32 getHeight() const override;
  virtual float getAspectRatio() const override;

  virtual void *getNativeWindow() const override;

  virtual bool isMinimized() const override;

  virtual void setVSync(bool enabled) override;
  virtual bool isSync() const override;

 private:
  GLFWwindowUniquePtr m_glfwWindow;
  WindowProps m_windowProps;
};
}  // namespace Neat