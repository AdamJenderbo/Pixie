#pragma once
#include <utility>
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Pixie
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};
}