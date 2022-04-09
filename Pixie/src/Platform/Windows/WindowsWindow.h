#pragma once
#include "Pixie/Window.h"
#include "GLFW/glfw3.h"
#include <string>

namespace Pixie
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(int width, int height, std::string title);
		~WindowsWindow();

		void Update();

	private:
		GLFWwindow* glfwWindow;
	};
}

