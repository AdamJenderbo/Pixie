#pragma once
#include <string>

namespace Pixie
{
	class Window
	{
	public:
		~Window() = default;

		virtual void Update() = 0;

		static Window* Create(int width, int height, std::string title);

	};
}

