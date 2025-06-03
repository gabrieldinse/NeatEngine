#pragma once

#include <memory>
#include <string>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Core/WindowProps.hpp"

namespace Neat {
class EventManager;
class Window {
 public:
  virtual ~Window() = default;

  virtual void onUpdate() = 0;

  virtual Int32 getWidth() const = 0;
  virtual Int32 getHeight() const = 0;
  virtual float getAspectRatio() const = 0;

  virtual void *getNativeWindow() const = 0;

  virtual bool isMinimized() const = 0;

  virtual void setVSync(bool enabled) = 0;
  virtual bool isSync() const = 0;

  static std::unique_ptr<Window> create(const WindowProps &props);
};
}  // namespace Neat