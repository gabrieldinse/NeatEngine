#pragma once

#include <iostream>

#include "Neat/Core/Types.h"


namespace Neat
{
	typedef enum class MouseCode : UInt16
	{
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
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<Int32>(mouseCode);
		return os;
	}
}

// Compatibility with glfw3.h -----------------------------------
#define NT_MOUSE_BUTTON_0        Neat::Mouse::Button0
#define NT_MOUSE_BUTTON_1        Neat::Mouse::Button1
#define NT_MOUSE_BUTTON_2        Neat::Mouse::Button2
#define NT_MOUSE_BUTTON_3        Neat::Mouse::Button3
#define NT_MOUSE_BUTTON_4        Neat::Mouse::Button4
#define NT_MOUSE_BUTTON_5        Neat::Mouse::Button5
#define NT_MOUSE_BUTTON_6        Neat::Mouse::Button6
#define NT_MOUSE_BUTTON_7        Neat::Mouse::Button7
#define NT_MOUSE_BUTTON_LAST     Neat::Mouse::ButtonLast
#define NT_MOUSE_BUTTON_LEFT     Neat::Mouse::ButtonLeft
#define NT_MOUSE_BUTTON_RIGHT    Neat::Mouse::ButtonRight
#define NT_MOUSE_BUTTON_MIDDLE   Neat::Mouse::ButtonMiddle
