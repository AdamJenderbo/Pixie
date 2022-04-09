#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Pixie
{
	Window* Pixie::Window::Create(int width, int height, std::string title)
	{
		return new WindowsWindow(width, height, title);
	}
}