#pragma once

#include "Core/Window.hpp"
#include "Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Neat {
struct WindowData {
  WindowProperties windowProperties;
  Ref<EventDispatcher> eventDispatcher;
};

class LinuxWindow : public Window {
 public:
  LinuxWindow(const Ref<EventDispatcher> &eventDispatcher,
              const WindowProperties &windowProperties);
  virtual ~LinuxWindow();

  virtual void update() override;

  virtual Int32 getWidth() const override;
  virtual Int32 getHeight() const override;
  virtual float getAspectRatio() const override;

  virtual void *getNativeWindow() const override;

  virtual bool isMinimized() const override;

  virtual void setVSync(bool enabled) override;
  virtual bool isVSync() const override;

 private:
  WindowData m_windowData;
  Scope<GraphicsContext> m_graphicsContext;
  GLFWwindow *m_glfwWindow = nullptr;
  static Int32 s_windowCount;
};
}  // namespace Neat