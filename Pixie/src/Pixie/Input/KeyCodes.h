#pragma once
#include <ostream>

namespace Pixie
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
#define PX_KEY_SPACE           ::Pixie::Key::Space
#define PX_KEY_APOSTROPHE      ::Pixie::Key::Apostrophe    /* ' */
#define PX_KEY_COMMA           ::Pixie::Key::Comma         /* , */
#define PX_KEY_MINUS           ::Pixie::Key::Minus         /* - */
#define PX_KEY_PERIOD          ::Pixie::Key::Period        /* . */
#define PX_KEY_SLASH           ::Pixie::Key::Slash         /* / */
#define PX_KEY_0               ::Pixie::Key::D0
#define PX_KEY_1               ::Pixie::Key::D1
#define PX_KEY_2               ::Pixie::Key::D2
#define PX_KEY_3               ::Pixie::Key::D3
#define PX_KEY_4               ::Pixie::Key::D4
#define PX_KEY_5               ::Pixie::Key::D5
#define PX_KEY_6               ::Pixie::Key::D6
#define PX_KEY_7               ::Pixie::Key::D7
#define PX_KEY_8               ::Pixie::Key::D8
#define PX_KEY_9               ::Pixie::Key::D9
#define PX_KEY_SEMICOLON       ::Pixie::Key::Semicolon     /* ; */
#define PX_KEY_EQUAL           ::Pixie::Key::Equal         /* = */
#define PX_KEY_A               ::Pixie::Key::A
#define PX_KEY_B               ::Pixie::Key::B
#define PX_KEY_C               ::Pixie::Key::C
#define PX_KEY_D               ::Pixie::Key::D
#define PX_KEY_E               ::Pixie::Key::E
#define PX_KEY_F               ::Pixie::Key::F
#define PX_KEY_G               ::Pixie::Key::G
#define PX_KEY_H               ::Pixie::Key::H
#define PX_KEY_I               ::Pixie::Key::I
#define PX_KEY_J               ::Pixie::Key::J
#define PX_KEY_K               ::Pixie::Key::K
#define PX_KEY_L               ::Pixie::Key::L
#define PX_KEY_M               ::Pixie::Key::M
#define PX_KEY_N               ::Pixie::Key::N
#define PX_KEY_O               ::Pixie::Key::O
#define PX_KEY_P               ::Pixie::Key::P
#define PX_KEY_Q               ::Pixie::Key::Q
#define PX_KEY_R               ::Pixie::Key::R
#define PX_KEY_S               ::Pixie::Key::S
#define PX_KEY_T               ::Pixie::Key::T
#define PX_KEY_U               ::Pixie::Key::U
#define PX_KEY_V               ::Pixie::Key::V
#define PX_KEY_W               ::Pixie::Key::W
#define PX_KEY_X               ::Pixie::Key::X
#define PX_KEY_Y               ::Pixie::Key::Y
#define PX_KEY_Z               ::Pixie::Key::Z
#define PX_KEY_LEFT_BRACKET    ::Pixie::Key::LeftBracket   /* [ */
#define PX_KEY_BACKSLASH       ::Pixie::Key::Backslash     /* \ */
#define PX_KEY_RIGHT_BRACKET   ::Pixie::Key::RightBracket  /* ] */
#define PX_KEY_GRAVE_ACCENT    ::Pixie::Key::GraveAccent   /* ` */
#define PX_KEY_WORLD_1         ::Pixie::Key::World1        /* non-US #1 */
#define PX_KEY_WORLD_2         ::Pixie::Key::World2        /* non-US #2 */

/* Function keys */
#define PX_KEY_ESCAPE          ::Pixie::Key::Escape
#define PX_KEY_ENTER           ::Pixie::Key::Enter
#define PX_KEY_TAB             ::Pixie::Key::Tab
#define PX_KEY_BACKSPACE       ::Pixie::Key::Backspace
#define PX_KEY_INSERT          ::Pixie::Key::Insert
#define PX_KEY_DELETE          ::Pixie::Key::Delete
#define PX_KEY_RIGHT           ::Pixie::Key::Right
#define PX_KEY_LEFT            ::Pixie::Key::Left
#define PX_KEY_DOWN            ::Pixie::Key::Down
#define PX_KEY_UP              ::Pixie::Key::Up
#define PX_KEY_PAGE_UP         ::Pixie::Key::PageUp
#define PX_KEY_PAGE_DOWN       ::Pixie::Key::PageDown
#define PX_KEY_HOME            ::Pixie::Key::Home
#define PX_KEY_END             ::Pixie::Key::End
#define PX_KEY_CAPS_LOCK       ::Pixie::Key::CapsLock
#define PX_KEY_SCROLL_LOCK     ::Pixie::Key::ScrollLock
#define PX_KEY_NUM_LOCK        ::Pixie::Key::NumLock
#define PX_KEY_PRINT_SCREEN    ::Pixie::Key::PrintScreen
#define PX_KEY_PAUSE           ::Pixie::Key::Pause
#define PX_KEY_F1              ::Pixie::Key::F1
#define PX_KEY_F2              ::Pixie::Key::F2
#define PX_KEY_F3              ::Pixie::Key::F3
#define PX_KEY_F4              ::Pixie::Key::F4
#define PX_KEY_F5              ::Pixie::Key::F5
#define PX_KEY_F6              ::Pixie::Key::F6
#define PX_KEY_F7              ::Pixie::Key::F7
#define PX_KEY_F8              ::Pixie::Key::F8
#define PX_KEY_F9              ::Pixie::Key::F9
#define PX_KEY_F10             ::Pixie::Key::F10
#define PX_KEY_F11             ::Pixie::Key::F11
#define PX_KEY_F12             ::Pixie::Key::F12
#define PX_KEY_F13             ::Pixie::Key::F13
#define PX_KEY_F14             ::Pixie::Key::F14
#define PX_KEY_F15             ::Pixie::Key::F15
#define PX_KEY_F16             ::Pixie::Key::F16
#define PX_KEY_F17             ::Pixie::Key::F17
#define PX_KEY_F18             ::Pixie::Key::F18
#define PX_KEY_F19             ::Pixie::Key::F19
#define PX_KEY_F20             ::Pixie::Key::F20
#define PX_KEY_F21             ::Pixie::Key::F21
#define PX_KEY_F22             ::Pixie::Key::F22
#define PX_KEY_F23             ::Pixie::Key::F23
#define PX_KEY_F24             ::Pixie::Key::F24
#define PX_KEY_F25             ::Pixie::Key::F25

/* Keypad */
#define PX_KEY_KP_0            ::Pixie::Key::KP0
#define PX_KEY_KP_1            ::Pixie::Key::KP1
#define PX_KEY_KP_2            ::Pixie::Key::KP2
#define PX_KEY_KP_3            ::Pixie::Key::KP3
#define PX_KEY_KP_4            ::Pixie::Key::KP4
#define PX_KEY_KP_5            ::Pixie::Key::KP5
#define PX_KEY_KP_6            ::Pixie::Key::KP6
#define PX_KEY_KP_7            ::Pixie::Key::KP7
#define PX_KEY_KP_8            ::Pixie::Key::KP8
#define PX_KEY_KP_9            ::Pixie::Key::KP9
#define PX_KEY_KP_DECIMAL      ::Pixie::Key::KPDecimal
#define PX_KEY_KP_DIVIDE       ::Pixie::Key::KPDivide
#define PX_KEY_KP_MULTIPLY     ::Pixie::Key::KPMultiply
#define PX_KEY_KP_SUBTRACT     ::Pixie::Key::KPSubtract
#define PX_KEY_KP_ADD          ::Pixie::Key::KPAdd
#define PX_KEY_KP_ENTER        ::Pixie::Key::KPEnter
#define PX_KEY_KP_EQUAL        ::Pixie::Key::KPEqual

#define PX_KEY_LEFT_SHIFT      ::Pixie::Key::LeftShift
#define PX_KEY_LEFT_CONTROL    ::Pixie::Key::LeftControl
#define PX_KEY_LEFT_ALT        ::Pixie::Key::LeftAlt
#define PX_KEY_LEFT_SUPER      ::Pixie::Key::LeftSuper
#define PX_KEY_RIGHT_SHIFT     ::Pixie::Key::RightShift
#define PX_KEY_RIGHT_CONTROL   ::Pixie::Key::RightControl
#define PX_KEY_RIGHT_ALT       ::Pixie::Key::RightAlt
#define PX_KEY_RIGHT_SUPER     ::Pixie::Key::RightSuper
#define PX_KEY_MENU            ::Pixie::Key::Menu