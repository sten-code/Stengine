#pragma once

namespace Sten
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

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
		Equal = 61, /* = */

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
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
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

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define ST_KEY_SPACE           ::Sten::Key::Space
#define ST_KEY_APOSTROPHE      ::Sten::Key::Apostrophe    /* ' */
#define ST_KEY_COMMA           ::Sten::Key::Comma         /* , */
#define ST_KEY_MINUS           ::Sten::Key::Minus         /* - */
#define ST_KEY_PERIOD          ::Sten::Key::Period        /* . */
#define ST_KEY_SLASH           ::Sten::Key::Slash         /* / */
#define ST_KEY_0               ::Sten::Key::D0
#define ST_KEY_1               ::Sten::Key::D1
#define ST_KEY_2               ::Sten::Key::D2
#define ST_KEY_3               ::Sten::Key::D3
#define ST_KEY_4               ::Sten::Key::D4
#define ST_KEY_5               ::Sten::Key::D5
#define ST_KEY_6               ::Sten::Key::D6
#define ST_KEY_7               ::Sten::Key::D7
#define ST_KEY_8               ::Sten::Key::D8
#define ST_KEY_9               ::Sten::Key::D9
#define ST_KEY_SEMICOLON       ::Sten::Key::Semicolon     /* ; */
#define ST_KEY_EQUAL           ::Sten::Key::Equal         /* = */
#define ST_KEY_A               ::Sten::Key::A
#define ST_KEY_B               ::Sten::Key::B
#define ST_KEY_C               ::Sten::Key::C
#define ST_KEY_D               ::Sten::Key::D
#define ST_KEY_E               ::Sten::Key::E
#define ST_KEY_F               ::Sten::Key::F
#define ST_KEY_G               ::Sten::Key::G
#define ST_KEY_H               ::Sten::Key::H
#define ST_KEY_I               ::Sten::Key::I
#define ST_KEY_J               ::Sten::Key::J
#define ST_KEY_K               ::Sten::Key::K
#define ST_KEY_L               ::Sten::Key::L
#define ST_KEY_M               ::Sten::Key::M
#define ST_KEY_N               ::Sten::Key::N
#define ST_KEY_O               ::Sten::Key::O
#define ST_KEY_P               ::Sten::Key::P
#define ST_KEY_Q               ::Sten::Key::Q
#define ST_KEY_R               ::Sten::Key::R
#define ST_KEY_S               ::Sten::Key::S
#define ST_KEY_T               ::Sten::Key::T
#define ST_KEY_U               ::Sten::Key::U
#define ST_KEY_V               ::Sten::Key::V
#define ST_KEY_W               ::Sten::Key::W
#define ST_KEY_X               ::Sten::Key::X
#define ST_KEY_Y               ::Sten::Key::Y
#define ST_KEY_Z               ::Sten::Key::Z
#define ST_KEY_LEFT_BRACKET    ::Sten::Key::LeftBracket   /* [ */
#define ST_KEY_BACKSLASH       ::Sten::Key::Backslash     /* \ */
#define ST_KEY_RIGHT_BRACKET   ::Sten::Key::RightBracket  /* ] */
#define ST_KEY_GRAVE_ACCENT    ::Sten::Key::GraveAccent   /* ` */
#define ST_KEY_WORLD_1         ::Sten::Key::World1        /* non-US #1 */
#define ST_KEY_WORLD_2         ::Sten::Key::World2        /* non-US #2 */

/* Function keys */
#define ST_KEY_ESCAPE          ::Sten::Key::Escape
#define ST_KEY_ENTER           ::Sten::Key::Enter
#define ST_KEY_TAB             ::Sten::Key::Tab
#define ST_KEY_BACKSPACE       ::Sten::Key::Backspace
#define ST_KEY_INSERT          ::Sten::Key::Insert
#define ST_KEY_DELETE          ::Sten::Key::Delete
#define ST_KEY_RIGHT           ::Sten::Key::Right
#define ST_KEY_LEFT            ::Sten::Key::Left
#define ST_KEY_DOWN            ::Sten::Key::Down
#define ST_KEY_UP              ::Sten::Key::Up
#define ST_KEY_PAGE_UP         ::Sten::Key::PageUp
#define ST_KEY_PAGE_DOWN       ::Sten::Key::PageDown
#define ST_KEY_HOME            ::Sten::Key::Home
#define ST_KEY_END             ::Sten::Key::End
#define ST_KEY_CAPS_LOCK       ::Sten::Key::CapsLock
#define ST_KEY_SCROLL_LOCK     ::Sten::Key::ScrollLock
#define ST_KEY_NUM_LOCK        ::Sten::Key::NumLock
#define ST_KEY_PRINT_SCREEN    ::Sten::Key::PrintScreen
#define ST_KEY_PAUSE           ::Sten::Key::Pause
#define ST_KEY_F1              ::Sten::Key::F1
#define ST_KEY_F2              ::Sten::Key::F2
#define ST_KEY_F3              ::Sten::Key::F3
#define ST_KEY_F4              ::Sten::Key::F4
#define ST_KEY_F5              ::Sten::Key::F5
#define ST_KEY_F6              ::Sten::Key::F6
#define ST_KEY_F7              ::Sten::Key::F7
#define ST_KEY_F8              ::Sten::Key::F8
#define ST_KEY_F9              ::Sten::Key::F9
#define ST_KEY_F10             ::Sten::Key::F10
#define ST_KEY_F11             ::Sten::Key::F11
#define ST_KEY_F12             ::Sten::Key::F12
#define ST_KEY_F13             ::Sten::Key::F13
#define ST_KEY_F14             ::Sten::Key::F14
#define ST_KEY_F15             ::Sten::Key::F15
#define ST_KEY_F16             ::Sten::Key::F16
#define ST_KEY_F17             ::Sten::Key::F17
#define ST_KEY_F18             ::Sten::Key::F18
#define ST_KEY_F19             ::Sten::Key::F19
#define ST_KEY_F20             ::Sten::Key::F20
#define ST_KEY_F21             ::Sten::Key::F21
#define ST_KEY_F22             ::Sten::Key::F22
#define ST_KEY_F23             ::Sten::Key::F23
#define ST_KEY_F24             ::Sten::Key::F24
#define ST_KEY_F25             ::Sten::Key::F25

/* Keypad */
#define ST_KEY_KP_0            ::Sten::Key::KP0
#define ST_KEY_KP_1            ::Sten::Key::KP1
#define ST_KEY_KP_2            ::Sten::Key::KP2
#define ST_KEY_KP_3            ::Sten::Key::KP3
#define ST_KEY_KP_4            ::Sten::Key::KP4
#define ST_KEY_KP_5            ::Sten::Key::KP5
#define ST_KEY_KP_6            ::Sten::Key::KP6
#define ST_KEY_KP_7            ::Sten::Key::KP7
#define ST_KEY_KP_8            ::Sten::Key::KP8
#define ST_KEY_KP_9            ::Sten::Key::KP9
#define ST_KEY_KP_DECIMAL      ::Sten::Key::KPDecimal
#define ST_KEY_KP_DIVIDE       ::Sten::Key::KPDivide
#define ST_KEY_KP_MULTIPLY     ::Sten::Key::KPMultiply
#define ST_KEY_KP_SUBTRACT     ::Sten::Key::KPSubtract
#define ST_KEY_KP_ADD          ::Sten::Key::KPAdd
#define ST_KEY_KP_ENTER        ::Sten::Key::KPEnter
#define ST_KEY_KP_EQUAL        ::Sten::Key::KPEqual

#define ST_KEY_LEFT_SHIFT      ::Sten::Key::LeftShift
#define ST_KEY_LEFT_CONTROL    ::Sten::Key::LeftControl
#define ST_KEY_LEFT_ALT        ::Sten::Key::LeftAlt
#define ST_KEY_LEFT_SUPER      ::Sten::Key::LeftSuper
#define ST_KEY_RIGHT_SHIFT     ::Sten::Key::RightShift
#define ST_KEY_RIGHT_CONTROL   ::Sten::Key::RightControl
#define ST_KEY_RIGHT_ALT       ::Sten::Key::RightAlt
#define ST_KEY_RIGHT_SUPER     ::Sten::Key::RightSuper
#define ST_KEY_MENU            ::Sten::Key::Menu
