#pragma once
#include <string>
#include "Event/Event.h"

namespace Pixie
{
	class Window
	{
	public:
		~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(std::function<void(Event&)> callback) = 0;

		virtual void* GetNativeWindow() = 0;

		static Window* Create(int width, int height, std::string title);

	};
}

