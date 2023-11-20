#pragma once

namespace Sten
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
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
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define ST_MOUSE_BUTTON_0      ::Sten::Mouse::Button0
#define ST_MOUSE_BUTTON_1      ::Sten::Mouse::Button1
#define ST_MOUSE_BUTTON_2      ::Sten::Mouse::Button2
#define ST_MOUSE_BUTTON_3      ::Sten::Mouse::Button3
#define ST_MOUSE_BUTTON_4      ::Sten::Mouse::Button4
#define ST_MOUSE_BUTTON_5      ::Sten::Mouse::Button5
#define ST_MOUSE_BUTTON_6      ::Sten::Mouse::Button6
#define ST_MOUSE_BUTTON_7      ::Sten::Mouse::Button7
#define ST_MOUSE_BUTTON_LAST   ::Sten::Mouse::ButtonLast
#define ST_MOUSE_BUTTON_LEFT   ::Sten::Mouse::ButtonLeft
#define ST_MOUSE_BUTTON_RIGHT  ::Sten::Mouse::ButtonRight
#define ST_MOUSE_BUTTON_MIDDLE ::Sten::Mouse::ButtonMiddle
