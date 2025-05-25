#pragma once

#include <functional>
#include <memory>
#include <string>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventManager.hpp"

struct GLFWwindow;

namespace Neat {
class Window {
public:
  struct WindowImpl;

  // WindowProps ----------------------------------------------------------
  struct WindowProps {
    std::string title;
    Int32 width;
    Int32 height;

    WindowProps(const std::string &title = "Neat Engine", Int32 width = 1280,
                Int32 height = 720)
        : title(title), width(width), height(height) {}
  };
  // ----------------------------------------------------------------------

public:
  Window(EventManager &eventManager, const WindowProps &props = WindowProps());
  ~Window();

  void swapBuffers();
  void pollEvents();

  Int32 getWidth() const;
  Int32 getHeight() const;
  float getAspectRatio() const;

  void *getNativeWindow() const;

  bool isMinimized() const;

  void setVSync(bool enabled);
  bool isSync() const;

private:
  std::unique_ptr<WindowImpl> m_impl;
};
} // namespace Neat