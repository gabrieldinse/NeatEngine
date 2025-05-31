#pragma once

#include <iostream>

#include "Neat/Core/Types.hpp"

namespace Neat {
enum class Mouse : UInt16 {
  Button0 = 0,
  Button1 = 1,
  Button2 = 2,
  Button3 = 3,
  Button4 = 4,
  Button5 = 5,
  Button6 = 6,
  Button7 = 7,
  ButtonLast = Button7,
  ButtonLeft = Button0,
  ButtonRight = Button1,
  ButtonMiddle = Button2
};

inline std::ostream &operator<<(std::ostream &os, Mouse mouseCode) {
  os << static_cast<Int32>(mouseCode);
  return os;
}

// Compatibility with glfw3.h -----------------------------------
constexpr auto MOUSE_BUTTON_0 = enumToInt(Mouse::Button0);
constexpr auto MOUSE_BUTTON_1 = enumToInt(Mouse::Button1);
constexpr auto MOUSE_BUTTON_2 = enumToInt(Mouse::Button2);
constexpr auto MOUSE_BUTTON_3 = enumToInt(Mouse::Button3);
constexpr auto MOUSE_BUTTON_4 = enumToInt(Mouse::Button4);
constexpr auto MOUSE_BUTTON_5 = enumToInt(Mouse::Button5);
constexpr auto MOUSE_BUTTON_6 = enumToInt(Mouse::Button6);
constexpr auto MOUSE_BUTTON_7 = enumToInt(Mouse::Button7);
constexpr auto MOUSE_BUTTON_LAST = enumToInt(Mouse::ButtonLast);
constexpr auto MOUSE_BUTTON_LEFT = enumToInt(Mouse::ButtonLeft);
constexpr auto MOUSE_BUTTON_RIGHT = enumToInt(Mouse::ButtonRight);
constexpr auto MOUSE_BUTTON_MIDDLE = enumToInt(Mouse::ButtonMiddle);
}  // namespace Neat
