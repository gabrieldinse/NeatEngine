#pragma once

#include <iostream>

#include "Neat/Core/Types.h"


namespace Neat
{
	typedef enum class KeyCode : UIntShort
	{
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		/* Command keys */
		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<Int>(keyCode);
		return os;
	}
}

// Compatibility with glfw3.h -----------------------------------
#define NT_KEY_SPACE           Neat::Key::Space
#define NT_KEY_APOSTROPHE      Neat::Key::Apostrophe    /* ' */
#define NT_KEY_COMMA           Neat::Key::Comma         /* , */
#define NT_KEY_MINUS           Neat::Key::Minus         /* - */
#define NT_KEY_PERIOD          Neat::Key::Period        /* . */
#define NT_KEY_SLASH           Neat::Key::Slash         /* / */
#define NT_KEY_0               Neat::Key::D0
#define NT_KEY_1               Neat::Key::D1
#define NT_KEY_2               Neat::Key::D2
#define NT_KEY_3               Neat::Key::D3
#define NT_KEY_4               Neat::Key::D4
#define NT_KEY_5               Neat::Key::D5
#define NT_KEY_6               Neat::Key::D6
#define NT_KEY_7               Neat::Key::D7
#define NT_KEY_8               Neat::Key::D8
#define NT_KEY_9               Neat::Key::D9
#define NT_KEY_SEMICOLON       Neat::Key::Semicolon     /* ; */
#define NT_KEY_EQUAL           Neat::Key::Equal         /* = */
#define NT_KEY_A               Neat::Key::A
#define NT_KEY_B               Neat::Key::B
#define NT_KEY_C               Neat::Key::C
#define NT_KEY_D               Neat::Key::D
#define NT_KEY_E               Neat::Key::E
#define NT_KEY_F               Neat::Key::F
#define NT_KEY_G               Neat::Key::G
#define NT_KEY_H               Neat::Key::H
#define NT_KEY_I               Neat::Key::I
#define NT_KEY_J               Neat::Key::J
#define NT_KEY_K               Neat::Key::K
#define NT_KEY_L               Neat::Key::L
#define NT_KEY_M               Neat::Key::M
#define NT_KEY_N               Neat::Key::N
#define NT_KEY_O               Neat::Key::O
#define NT_KEY_P               Neat::Key::P
#define NT_KEY_Q               Neat::Key::Q
#define NT_KEY_R               Neat::Key::R
#define NT_KEY_S               Neat::Key::S
#define NT_KEY_T               Neat::Key::T
#define NT_KEY_U               Neat::Key::U
#define NT_KEY_V               Neat::Key::V
#define NT_KEY_W               Neat::Key::W
#define NT_KEY_X               Neat::Key::X
#define NT_KEY_Y               Neat::Key::Y
#define NT_KEY_Z               Neat::Key::Z
#define NT_KEY_LEFT_BRACKET    Neat::Key::LeftBracket   /* [ */
#define NT_KEY_BACKSLASH       Neat::Key::Backslash     /* \ */
#define NT_KEY_RIGHT_BRACKET   Neat::Key::RightBracket  /* ] */
#define NT_KEY_GRAVE_ACCENT    Neat::Key::GraveAccent   /* ` */
#define NT_KEY_WORLD_1         Neat::Key::World1        /* non-US #1 */
#define NT_KEY_WORLD_2         Neat::Key::World2        /* non-US #2 */

/* Function keys */
#define NT_KEY_ESCAPE          Neat::Key::Escape
#define NT_KEY_ENTER           Neat::Key::Enter
#define NT_KEY_TAB             Neat::Key::Tab
#define NT_KEY_BACKSPACE       Neat::Key::Backspace
#define NT_KEY_INSERT          Neat::Key::Insert
#define NT_KEY_DELETE          Neat::Key::Delete
#define NT_KEY_RIGHT           Neat::Key::Right
#define NT_KEY_LEFT            Neat::Key::Left
#define NT_KEY_DOWN            Neat::Key::Down
#define NT_KEY_UP              Neat::Key::Up
#define NT_KEY_PAGE_UP         Neat::Key::PageUp
#define NT_KEY_PAGE_DOWN       Neat::Key::PageDown
#define NT_KEY_HOME            Neat::Key::Home
#define NT_KEY_END             Neat::Key::End
#define NT_KEY_CAPS_LOCK       Neat::Key::CapsLock
#define NT_KEY_SCROLL_LOCK     Neat::Key::ScrollLock
#define NT_KEY_NUM_LOCK        Neat::Key::NumLock
#define NT_KEY_PRINT_SCREEN    Neat::Key::PrintScreen
#define NT_KEY_PAUSE           Neat::Key::Pause
#define NT_KEY_F1              Neat::Key::F1
#define NT_KEY_F2              Neat::Key::F2
#define NT_KEY_F3              Neat::Key::F3
#define NT_KEY_F4              Neat::Key::F4
#define NT_KEY_F5              Neat::Key::F5
#define NT_KEY_F6              Neat::Key::F6
#define NT_KEY_F7              Neat::Key::F7
#define NT_KEY_F8              Neat::Key::F8
#define NT_KEY_F9              Neat::Key::F9
#define NT_KEY_F10             Neat::Key::F10
#define NT_KEY_F11             Neat::Key::F11
#define NT_KEY_F12             Neat::Key::F12
#define NT_KEY_F13             Neat::Key::F13
#define NT_KEY_F14             Neat::Key::F14
#define NT_KEY_F15             Neat::Key::F15
#define NT_KEY_F16             Neat::Key::F16
#define NT_KEY_F17             Neat::Key::F17
#define NT_KEY_F18             Neat::Key::F18
#define NT_KEY_F19             Neat::Key::F19
#define NT_KEY_F20             Neat::Key::F20
#define NT_KEY_F21             Neat::Key::F21
#define NT_KEY_F22             Neat::Key::F22
#define NT_KEY_F23             Neat::Key::F23
#define NT_KEY_F24             Neat::Key::F24
#define NT_KEY_F25             Neat::Key::F25

/* Keypad */
#define NT_KEY_KP_0            Neat::Key::KP0
#define NT_KEY_KP_1            Neat::Key::KP1
#define NT_KEY_KP_2            Neat::Key::KP2
#define NT_KEY_KP_3            Neat::Key::KP3
#define NT_KEY_KP_4            Neat::Key::KP4
#define NT_KEY_KP_5            Neat::Key::KP5
#define NT_KEY_KP_6            Neat::Key::KP6
#define NT_KEY_KP_7            Neat::Key::KP7
#define NT_KEY_KP_8            Neat::Key::KP8
#define NT_KEY_KP_9            Neat::Key::KP9
#define NT_KEY_KP_DECIMAL      Neat::Key::KPDecimal
#define NT_KEY_KP_DIVIDE       Neat::Key::KPDivide
#define NT_KEY_KP_MULTIPLY     Neat::Key::KPMultiply
#define NT_KEY_KP_SUBTRACT     Neat::Key::KPSubtract
#define NT_KEY_KP_ADD          Neat::Key::KPAdd
#define NT_KEY_KP_ENTER        Neat::Key::KPEnter
#define NT_KEY_KP_EQUAL        Neat::Key::KPEqual

/* Command keys */
#define NT_KEY_LEFT_SHIFT      Neat::Key::LeftShift
#define NT_KEY_LEFT_CONTROL    Neat::Key::LeftControl
#define NT_KEY_LEFT_ALT        Neat::Key::LeftAlt
#define NT_KEY_LEFT_SUPER      Neat::Key::LeftSuper
#define NT_KEY_RIGHT_SHIFT     Neat::Key::RightShift
#define NT_KEY_RIGHT_CONTROL   Neat::Key::RightControl
#define NT_KEY_RIGHT_ALT       Neat::Key::RightAlt
#define NT_KEY_RIGHT_SUPER     Neat::Key::RightSuper
#define NT_KEY_MENU            Neat::Key::Menu
