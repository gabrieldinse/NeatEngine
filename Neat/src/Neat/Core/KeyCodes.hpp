#pragma once

#include <iostream>

#include "Neat/Core/Types.hpp"

namespace Neat {
enum class Key : UInt16 {
  Space = 32,
  Apostrophe = 39, /* ' */
  Comma = 44,      /* , */
  Minus = 45,      /* - */
  Period = 46,     /* . */
  Slash = 47,      /* / */

  D0 = 48, /* 0 */
  D1 = 49, /* 1 */
  D2 = 50, /* 2 */
  D3 = 51, /* 3 */
  D4 = 52, /* 4 */
  D5 = 53, /* 5 */
  D6 = 54, /* 6 */
  D7 = 55, /* 7 */
  D8 = 56, /* 8 */
  D9 = 57, /* 9 */

  Semicolon = 59, /* ; */
  Equal = 61,     /* = */

  A = 65,
  B = 66,
  C = 67,
  D = 68,
  E = 69,
  F = 70,
  G = 71,
  H = 72,
  I = 73,
  J = 74,
  K = 75,
  L = 76,
  M = 77,
  N = 78,
  O = 79,
  P = 80,
  Q = 81,
  R = 82,
  S = 83,
  T = 84,
  U = 85,
  V = 86,
  W = 87,
  X = 88,
  Y = 89,
  Z = 90,

  LeftBracket = 91,  /* [ */
  Backslash = 92,    /* \ */
  RightBracket = 93, /* ] */
  GraveAccent = 96,  /* ` */

  World1 = 161, /* non-US #1 */
  World2 = 162, /* non-US #2 */

  /* Function keys */
  Escape = 256,
  Enter = 257,
  Tab = 258,
  Backspace = 259,
  Insert = 260,
  Delete = 261,
  Right = 262,
  Left = 263,
  Down = 264,
  Up = 265,
  PageUp = 266,
  PageDown = 267,
  Home = 268,
  End = 269,
  CapsLock = 280,
  ScrollLock = 281,
  NumLock = 282,
  PrintScreen = 283,
  Pause = 284,
  F1 = 290,
  F2 = 291,
  F3 = 292,
  F4 = 293,
  F5 = 294,
  F6 = 295,
  F7 = 296,
  F8 = 297,
  F9 = 298,
  F10 = 299,
  F11 = 300,
  F12 = 301,
  F13 = 302,
  F14 = 303,
  F15 = 304,
  F16 = 305,
  F17 = 306,
  F18 = 307,
  F19 = 308,
  F20 = 309,
  F21 = 310,
  F22 = 311,
  F23 = 312,
  F24 = 313,
  F25 = 314,

  /* Keypad */
  KP0 = 320,
  KP1 = 321,
  KP2 = 322,
  KP3 = 323,
  KP4 = 324,
  KP5 = 325,
  KP6 = 326,
  KP7 = 327,
  KP8 = 328,
  KP9 = 329,
  KPDecimal = 330,
  KPDivide = 331,
  KPMultiply = 332,
  KPSubtract = 333,
  KPAdd = 334,
  KPEnter = 335,
  KPEqual = 336,

  /* Command keys */
  LeftShift = 340,
  LeftControl = 341,
  LeftAlt = 342,
  LeftSuper = 343,
  RightShift = 344,
  RightControl = 345,
  RightAlt = 346,
  RightSuper = 347,
  Menu = 348
};

inline std::ostream &operator<<(std::ostream &os, Key key) {
  os << static_cast<Int32>(key);
  return os;
}

template <typename E>
constexpr typename std::enable_if<std::is_enum<E>::value,
                                  std::underlying_type_t<E>>::type
enumToInt(E e) {
  return static_cast<std::underlying_type_t<E>>(e);
}

// Compatibility with glfw3.h -----------------------------------
constexpr auto KEY_SPACE = Neat::enumToInt(Neat::Key::Space);
constexpr auto KEY_APOSTROPHE = Neat::enumToInt(Neat::Key::Apostrophe); /* ' */
constexpr auto KEY_COMMA = Neat::enumToInt(Neat::Key::Comma);           /* , */
constexpr auto KEY_MINUS = Neat::enumToInt(Neat::Key::Minus);           /* - */
constexpr auto KEY_PERIOD = Neat::enumToInt(Neat::Key::Period);         /* . */
constexpr auto KEY_SLASH = Neat::enumToInt(Neat::Key::Slash);           /* / */
constexpr auto KEY_0 = Neat::enumToInt(Neat::Key::D0);
constexpr auto KEY_1 = Neat::enumToInt(Neat::Key::D1);
constexpr auto KEY_2 = Neat::enumToInt(Neat::Key::D2);
constexpr auto KEY_3 = Neat::enumToInt(Neat::Key::D3);
constexpr auto KEY_4 = Neat::enumToInt(Neat::Key::D4);
constexpr auto KEY_5 = Neat::enumToInt(Neat::Key::D5);
constexpr auto KEY_6 = Neat::enumToInt(Neat::Key::D6);
constexpr auto KEY_7 = Neat::enumToInt(Neat::Key::D7);
constexpr auto KEY_8 = Neat::enumToInt(Neat::Key::D8);
constexpr auto KEY_9 = Neat::enumToInt(Neat::Key::D9);
constexpr auto KEY_SEMICOLON = Neat::enumToInt(Neat::Key::Semicolon); /* ; */
constexpr auto KEY_EQUAL = Neat::enumToInt(Neat::Key::Equal);         /* = */
constexpr auto KEY_A = Neat::enumToInt(Neat::Key::A);
constexpr auto KEY_B = Neat::enumToInt(Neat::Key::B);
constexpr auto KEY_C = Neat::enumToInt(Neat::Key::C);
constexpr auto KEY_D = Neat::enumToInt(Neat::Key::D);
constexpr auto KEY_E = Neat::enumToInt(Neat::Key::E);
constexpr auto KEY_F = Neat::enumToInt(Neat::Key::F);
constexpr auto KEY_G = Neat::enumToInt(Neat::Key::G);
constexpr auto KEY_H = Neat::enumToInt(Neat::Key::H);
constexpr auto KEY_I = Neat::enumToInt(Neat::Key::I);
constexpr auto KEY_J = Neat::enumToInt(Neat::Key::J);
constexpr auto KEY_K = Neat::enumToInt(Neat::Key::K);
constexpr auto KEY_L = Neat::enumToInt(Neat::Key::L);
constexpr auto KEY_M = Neat::enumToInt(Neat::Key::M);
constexpr auto KEY_N = Neat::enumToInt(Neat::Key::N);
constexpr auto KEY_O = Neat::enumToInt(Neat::Key::O);
constexpr auto KEY_P = Neat::enumToInt(Neat::Key::P);
constexpr auto KEY_Q = Neat::enumToInt(Neat::Key::Q);
constexpr auto KEY_R = Neat::enumToInt(Neat::Key::R);
constexpr auto KEY_S = Neat::enumToInt(Neat::Key::S);
constexpr auto KEY_T = Neat::enumToInt(Neat::Key::T);
constexpr auto KEY_U = Neat::enumToInt(Neat::Key::U);
constexpr auto KEY_V = Neat::enumToInt(Neat::Key::V);
constexpr auto KEY_W = Neat::enumToInt(Neat::Key::W);
constexpr auto KEY_X = Neat::enumToInt(Neat::Key::X);
constexpr auto KEY_Y = Neat::enumToInt(Neat::Key::Y);
constexpr auto KEY_Z = Neat::enumToInt(Neat::Key::Z);
constexpr auto KEY_LEFT_BRACKET =
    Neat::enumToInt(Neat::Key::LeftBracket);                          /* [ */
constexpr auto KEY_BACKSLASH = Neat::enumToInt(Neat::Key::Backslash); /* \ */
constexpr auto KEY_RIGHT_BRACKET =
    Neat::enumToInt(Neat::Key::RightBracket); /* ] */
constexpr auto KEY_GRAVE_ACCENT =
    Neat::enumToInt(Neat::Key::GraveAccent);                     /* ` */
constexpr auto KEY_WORLD_1 = Neat::enumToInt(Neat::Key::World1); /* non-US #1 */
constexpr auto KEY_WORLD_2 = Neat::enumToInt(Neat::Key::World2); /* non-US #2 */

/* Function keys */
constexpr auto KEY_ESCAPE = Neat::enumToInt(Neat::Key::Escape);
constexpr auto KEY_ENTER = Neat::enumToInt(Neat::Key::Enter);
constexpr auto KEY_TAB = Neat::enumToInt(Neat::Key::Tab);
constexpr auto KEY_BACKSPACE = Neat::enumToInt(Neat::Key::Backspace);
constexpr auto KEY_INSERT = Neat::enumToInt(Neat::Key::Insert);
constexpr auto KEY_DELETE = Neat::enumToInt(Neat::Key::Delete);
constexpr auto KEY_RIGHT = Neat::enumToInt(Neat::Key::Right);
constexpr auto KEY_LEFT = Neat::enumToInt(Neat::Key::Left);
constexpr auto KEY_DOWN = Neat::enumToInt(Neat::Key::Down);
constexpr auto KEY_UP = Neat::enumToInt(Neat::Key::Up);
constexpr auto KEY_PAGE_UP = Neat::enumToInt(Neat::Key::PageUp);
constexpr auto KEY_PAGE_DOWN = Neat::enumToInt(Neat::Key::PageDown);
constexpr auto KEY_HOME = Neat::enumToInt(Neat::Key::Home);
constexpr auto KEY_END = Neat::enumToInt(Neat::Key::End);
constexpr auto KEY_CAPS_LOCK = Neat::enumToInt(Neat::Key::CapsLock);
constexpr auto KEY_SCROLL_LOCK = Neat::enumToInt(Neat::Key::ScrollLock);
constexpr auto KEY_NUM_LOCK = Neat::enumToInt(Neat::Key::NumLock);
constexpr auto KEY_PRINT_SCREEN = Neat::enumToInt(Neat::Key::PrintScreen);
constexpr auto KEY_PAUSE = Neat::enumToInt(Neat::Key::Pause);
constexpr auto KEY_F1 = Neat::enumToInt(Neat::Key::F1);
constexpr auto KEY_F2 = Neat::enumToInt(Neat::Key::F2);
constexpr auto KEY_F3 = Neat::enumToInt(Neat::Key::F3);
constexpr auto KEY_F4 = Neat::enumToInt(Neat::Key::F4);
constexpr auto KEY_F5 = Neat::enumToInt(Neat::Key::F5);
constexpr auto KEY_F6 = Neat::enumToInt(Neat::Key::F6);
constexpr auto KEY_F7 = Neat::enumToInt(Neat::Key::F7);
constexpr auto KEY_F8 = Neat::enumToInt(Neat::Key::F8);
constexpr auto KEY_F9 = Neat::enumToInt(Neat::Key::F9);
constexpr auto KEY_F10 = Neat::enumToInt(Neat::Key::F10);
constexpr auto KEY_F11 = Neat::enumToInt(Neat::Key::F11);
constexpr auto KEY_F12 = Neat::enumToInt(Neat::Key::F12);
constexpr auto KEY_F13 = Neat::enumToInt(Neat::Key::F13);
constexpr auto KEY_F14 = Neat::enumToInt(Neat::Key::F14);
constexpr auto KEY_F15 = Neat::enumToInt(Neat::Key::F15);
constexpr auto KEY_F16 = Neat::enumToInt(Neat::Key::F16);
constexpr auto KEY_F17 = Neat::enumToInt(Neat::Key::F17);
constexpr auto KEY_F18 = Neat::enumToInt(Neat::Key::F18);
constexpr auto KEY_F19 = Neat::enumToInt(Neat::Key::F19);
constexpr auto KEY_F20 = Neat::enumToInt(Neat::Key::F20);
constexpr auto KEY_F21 = Neat::enumToInt(Neat::Key::F21);
constexpr auto KEY_F22 = Neat::enumToInt(Neat::Key::F22);
constexpr auto KEY_F23 = Neat::enumToInt(Neat::Key::F23);
constexpr auto KEY_F24 = Neat::enumToInt(Neat::Key::F24);
constexpr auto KEY_F25 = Neat::enumToInt(Neat::Key::F25);

/* Keypad */
constexpr auto KEY_KP_0 = Neat::enumToInt(Neat::Key::KP0);
constexpr auto KEY_KP_1 = Neat::enumToInt(Neat::Key::KP1);
constexpr auto KEY_KP_2 = Neat::enumToInt(Neat::Key::KP2);
constexpr auto KEY_KP_3 = Neat::enumToInt(Neat::Key::KP3);
constexpr auto KEY_KP_4 = Neat::enumToInt(Neat::Key::KP4);
constexpr auto KEY_KP_5 = Neat::enumToInt(Neat::Key::KP5);
constexpr auto KEY_KP_6 = Neat::enumToInt(Neat::Key::KP6);
constexpr auto KEY_KP_7 = Neat::enumToInt(Neat::Key::KP7);
constexpr auto KEY_KP_8 = Neat::enumToInt(Neat::Key::KP8);
constexpr auto KEY_KP_9 = Neat::enumToInt(Neat::Key::KP9);
constexpr auto KEY_KP_DECIMAL = Neat::enumToInt(Neat::Key::KPDecimal);
constexpr auto KEY_KP_DIVIDE = Neat::enumToInt(Neat::Key::KPDivide);
constexpr auto KEY_KP_MULTIPLY = Neat::enumToInt(Neat::Key::KPMultiply);
constexpr auto KEY_KP_SUBTRACT = Neat::enumToInt(Neat::Key::KPSubtract);
constexpr auto KEY_KP_ADD = Neat::enumToInt(Neat::Key::KPAdd);
constexpr auto KEY_KP_ENTER = Neat::enumToInt(Neat::Key::KPEnter);
constexpr auto KEY_KP_EQUAL = Neat::enumToInt(Neat::Key::KPEqual);

/* Command keys */
constexpr auto KEY_LEFT_SHIFT = Neat::enumToInt(Neat::Key::LeftShift);
constexpr auto KEY_LEFT_CONTROL = Neat::enumToInt(Neat::Key::LeftControl);
constexpr auto KEY_LEFT_ALT = Neat::enumToInt(Neat::Key::LeftAlt);
constexpr auto KEY_LEFT_SUPER = Neat::enumToInt(Neat::Key::LeftSuper);
constexpr auto KEY_RIGHT_SHIFT = Neat::enumToInt(Neat::Key::RightShift);
constexpr auto KEY_RIGHT_CONTROL = Neat::enumToInt(Neat::Key::RightControl);
constexpr auto KEY_RIGHT_ALT = Neat::enumToInt(Neat::Key::RightAlt);
constexpr auto KEY_RIGHT_SUPER = Neat::enumToInt(Neat::Key::RightSuper);
constexpr auto KEY_MENU = Neat::enumToInt(Neat::Key::Menu);
}  // namespace Neat
