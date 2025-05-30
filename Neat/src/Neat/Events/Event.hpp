#pragma once

#include "Neat/Core/KeyCodes.hpp"
#include "Neat/Core/MouseCodes.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
class EventManager;

// ---------------------------------------------------------------------- //
// BaseEvent ------------------------------------------------------------ //
// ---------------------------------------------------------------------- //
class BaseEvent {
public:
  using Family = UInt32;

  virtual ~BaseEvent() {}

protected:
  static Family s_familyCounter;
};

// ---------------------------------------------------------------------- //
// Event ---------------------------------------------------------------- //
// ---------------------------------------------------------------------- //
template <typename Derived> class Event : public BaseEvent {
private:
  friend class EventManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    return family;
  }
};

// ---------------------------------------------------------------------- //
// Window events -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct WindowResizeEvent {
  WindowResizeEvent(UInt32 width, UInt32 height)
      : width(width), height(height) {}

  UInt32 width;
  UInt32 height;
};

struct WindowCloseEvent {
  WindowCloseEvent() = default;
};

// ---------------------------------------------------------------------- //
// Mouse events --------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct MouseButtonEvent {
  MouseCode button;

protected:
  MouseButtonEvent(MouseCode button) : button(button) {}
};

struct MouseButtonPressedEvent : public MouseButtonEvent {
  MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}
};

struct MouseButtonReleasedEvent : public MouseButtonEvent {
  MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}
};

struct MouseMovedEvent {
  MouseMovedEvent(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

  float xPos;
  float yPos;
};

struct MouseScrolledEvent {
public:
  MouseScrolledEvent(float xOffset, float yOffset)
      : xOffset(xOffset), yOffset(yOffset) {}

  float xOffset;
  float yOffset;
};

// ---------------------------------------------------------------------- //
// Key events ----------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct KeyEvent {
  Key key;

protected:
  KeyEvent(Key key) : key(key) {}
};

struct KeyPressedEvent : public KeyEvent {
  KeyPressedEvent(Key key, Int32 repeatCount = 0)
      : KeyEvent(key), repeatCount(repeatCount) {}

  Int32 repeatCount;
};

struct KeyReleasedEvent : public KeyEvent {
  KeyReleasedEvent(Key key) : KeyEvent(key) {}
};

struct KeyTypedEvent : public KeyEvent {
  KeyTypedEvent(Key key) : KeyEvent(key) {}
};
} // namespace Neat