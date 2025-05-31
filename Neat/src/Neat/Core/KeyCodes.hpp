#pragma once

#include <iostream>

#include "Neat/Core/Types.hpp"
#include "Neat/Helper/TypeConversions.hpp"

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

// Compatibility with glfw3.h -----------------------------------
constexpr auto KEY_SPACE = enumToInt(Key::Space);
constexpr auto KEY_APOSTROPHE = enumToInt(Key::Apostrophe); /* ' */
constexpr auto KEY_COMMA = enumToInt(Key::Comma);           /* , */
constexpr auto KEY_MINUS = enumToInt(Key::Minus);           /* - */
constexpr auto KEY_PERIOD = enumToInt(Key::Period);         /* . */
constexpr auto KEY_SLASH = enumToInt(Key::Slash);           /* / */
constexpr auto KEY_0 = enumToInt(Key::D0);
constexpr auto KEY_1 = enumToInt(Key::D1);
constexpr auto KEY_2 = enumToInt(Key::D2);
constexpr auto KEY_3 = enumToInt(Key::D3);
constexpr auto KEY_4 = enumToInt(Key::D4);
constexpr auto KEY_5 = enumToInt(Key::D5);
constexpr auto KEY_6 = enumToInt(Key::D6);
constexpr auto KEY_7 = enumToInt(Key::D7);
constexpr auto KEY_8 = enumToInt(Key::D8);
constexpr auto KEY_9 = enumToInt(Key::D9);
constexpr auto KEY_SEMICOLON = enumToInt(Key::Semicolon); /* ; */
constexpr auto KEY_EQUAL = enumToInt(Key::Equal);         /* = */
constexpr auto KEY_A = enumToInt(Key::A);
constexpr auto KEY_B = enumToInt(Key::B);
constexpr auto KEY_C = enumToInt(Key::C);
constexpr auto KEY_D = enumToInt(Key::D);
constexpr auto KEY_E = enumToInt(Key::E);
constexpr auto KEY_F = enumToInt(Key::F);
constexpr auto KEY_G = enumToInt(Key::G);
constexpr auto KEY_H = enumToInt(Key::H);
constexpr auto KEY_I = enumToInt(Key::I);
constexpr auto KEY_J = enumToInt(Key::J);
constexpr auto KEY_K = enumToInt(Key::K);
constexpr auto KEY_L = enumToInt(Key::L);
constexpr auto KEY_M = enumToInt(Key::M);
constexpr auto KEY_N = enumToInt(Key::N);
constexpr auto KEY_O = enumToInt(Key::O);
constexpr auto KEY_P = enumToInt(Key::P);
constexpr auto KEY_Q = enumToInt(Key::Q);
constexpr auto KEY_R = enumToInt(Key::R);
constexpr auto KEY_S = enumToInt(Key::S);
constexpr auto KEY_T = enumToInt(Key::T);
constexpr auto KEY_U = enumToInt(Key::U);
constexpr auto KEY_V = enumToInt(Key::V);
constexpr auto KEY_W = enumToInt(Key::W);
constexpr auto KEY_X = enumToInt(Key::X);
constexpr auto KEY_Y = enumToInt(Key::Y);
constexpr auto KEY_Z = enumToInt(Key::Z);
constexpr auto KEY_LEFT_BRACKET = enumToInt(Key::LeftBracket);   /* [ */
constexpr auto KEY_BACKSLASH = enumToInt(Key::Backslash);        /* \ */
constexpr auto KEY_RIGHT_BRACKET = enumToInt(Key::RightBracket); /* ] */
constexpr auto KEY_GRAVE_ACCENT = enumToInt(Key::GraveAccent);   /* ` */
constexpr auto KEY_WORLD_1 = enumToInt(Key::World1);             /* non-US #1 */
constexpr auto KEY_WORLD_2 = enumToInt(Key::World2);             /* non-US #2 */

/* Function keys */
constexpr auto KEY_ESCAPE = enumToInt(Key::Escape);
constexpr auto KEY_ENTER = enumToInt(Key::Enter);
constexpr auto KEY_TAB = enumToInt(Key::Tab);
constexpr auto KEY_BACKSPACE = enumToInt(Key::Backspace);
constexpr auto KEY_INSERT = enumToInt(Key::Insert);
constexpr auto KEY_DELETE = enumToInt(Key::Delete);
constexpr auto KEY_RIGHT = enumToInt(Key::Right);
constexpr auto KEY_LEFT = enumToInt(Key::Left);
constexpr auto KEY_DOWN = enumToInt(Key::Down);
constexpr auto KEY_UP = enumToInt(Key::Up);
constexpr auto KEY_PAGE_UP = enumToInt(Key::PageUp);
constexpr auto KEY_PAGE_DOWN = enumToInt(Key::PageDown);
constexpr auto KEY_HOME = enumToInt(Key::Home);
constexpr auto KEY_END = enumToInt(Key::End);
constexpr auto KEY_CAPS_LOCK = enumToInt(Key::CapsLock);
constexpr auto KEY_SCROLL_LOCK = enumToInt(Key::ScrollLock);
constexpr auto KEY_NUM_LOCK = enumToInt(Key::NumLock);
constexpr auto KEY_PRINT_SCREEN = enumToInt(Key::PrintScreen);
constexpr auto KEY_PAUSE = enumToInt(Key::Pause);
constexpr auto KEY_F1 = enumToInt(Key::F1);
constexpr auto KEY_F2 = enumToInt(Key::F2);
constexpr auto KEY_F3 = enumToInt(Key::F3);
constexpr auto KEY_F4 = enumToInt(Key::F4);
constexpr auto KEY_F5 = enumToInt(Key::F5);
constexpr auto KEY_F6 = enumToInt(Key::F6);
constexpr auto KEY_F7 = enumToInt(Key::F7);
constexpr auto KEY_F8 = enumToInt(Key::F8);
constexpr auto KEY_F9 = enumToInt(Key::F9);
constexpr auto KEY_F10 = enumToInt(Key::F10);
constexpr auto KEY_F11 = enumToInt(Key::F11);
constexpr auto KEY_F12 = enumToInt(Key::F12);
constexpr auto KEY_F13 = enumToInt(Key::F13);
constexpr auto KEY_F14 = enumToInt(Key::F14);
constexpr auto KEY_F15 = enumToInt(Key::F15);
constexpr auto KEY_F16 = enumToInt(Key::F16);
constexpr auto KEY_F17 = enumToInt(Key::F17);
constexpr auto KEY_F18 = enumToInt(Key::F18);
constexpr auto KEY_F19 = enumToInt(Key::F19);
constexpr auto KEY_F20 = enumToInt(Key::F20);
constexpr auto KEY_F21 = enumToInt(Key::F21);
constexpr auto KEY_F22 = enumToInt(Key::F22);
constexpr auto KEY_F23 = enumToInt(Key::F23);
constexpr auto KEY_F24 = enumToInt(Key::F24);
constexpr auto KEY_F25 = enumToInt(Key::F25);

/* Keypad */
constexpr auto KEY_KP_0 = enumToInt(Key::KP0);
constexpr auto KEY_KP_1 = enumToInt(Key::KP1);
constexpr auto KEY_KP_2 = enumToInt(Key::KP2);
constexpr auto KEY_KP_3 = enumToInt(Key::KP3);
constexpr auto KEY_KP_4 = enumToInt(Key::KP4);
constexpr auto KEY_KP_5 = enumToInt(Key::KP5);
constexpr auto KEY_KP_6 = enumToInt(Key::KP6);
constexpr auto KEY_KP_7 = enumToInt(Key::KP7);
constexpr auto KEY_KP_8 = enumToInt(Key::KP8);
constexpr auto KEY_KP_9 = enumToInt(Key::KP9);
constexpr auto KEY_KP_DECIMAL = enumToInt(Key::KPDecimal);
constexpr auto KEY_KP_DIVIDE = enumToInt(Key::KPDivide);
constexpr auto KEY_KP_MULTIPLY = enumToInt(Key::KPMultiply);
constexpr auto KEY_KP_SUBTRACT = enumToInt(Key::KPSubtract);
constexpr auto KEY_KP_ADD = enumToInt(Key::KPAdd);
constexpr auto KEY_KP_ENTER = enumToInt(Key::KPEnter);
constexpr auto KEY_KP_EQUAL = enumToInt(Key::KPEqual);

/* Command keys */
constexpr auto KEY_LEFT_SHIFT = enumToInt(Key::LeftShift);
constexpr auto KEY_LEFT_CONTROL = enumToInt(Key::LeftControl);
constexpr auto KEY_LEFT_ALT = enumToInt(Key::LeftAlt);
constexpr auto KEY_LEFT_SUPER = enumToInt(Key::LeftSuper);
constexpr auto KEY_RIGHT_SHIFT = enumToInt(Key::RightShift);
constexpr auto KEY_RIGHT_CONTROL = enumToInt(Key::RightControl);
constexpr auto KEY_RIGHT_ALT = enumToInt(Key::RightAlt);
constexpr auto KEY_RIGHT_SUPER = enumToInt(Key::RightSuper);
constexpr auto KEY_MENU = enumToInt(Key::Menu);
}  // namespace Neat
