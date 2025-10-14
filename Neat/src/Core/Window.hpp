#pragma once

#include <memory>
#include <string>

#include "PlatformDetection.hpp"
#include "Types.hpp"
#include "WindowProperties.hpp"

#include "EventDispatching/EventDispatcher.hpp"
#include "Core/Window.hpp"
#include "Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Neat {
struct WindowData {
  WindowProperties windowProperties;
  Ref<EventDispatcher> eventDispatcher;
};

class Window {
 public:
  Window(const Ref<EventDispatcher> &eventDispatcher,
              const WindowProperties &windowProperties);
  ~Window();

  void update();

  Int32 getWidth() const;
  Int32 getHeight() const;
  float getAspectRatio() const;

  GLFWwindow *getNativeWindow() const;

  bool isMinimized() const;

  void setVSync(bool enabled);
  bool isVSync() const;

 private:
  WindowData m_windowData;
  Scope<GraphicsContext> m_graphicsContext;
  GLFWwindow *m_glfwWindow = nullptr;
  static Int32 s_windowCount;
};
}  // namespace Neat