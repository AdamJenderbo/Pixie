#pragma once
#include "Pixie/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <vector>

namespace Pixie
{
	struct WindowData
	{
		int Width;
		int Height;
		std::string Title;
		std::function<void(Event&)> EventCallback;
	};

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(int width, int height, std::string title);
		~WindowsWindow();

		void OnUpdate();

		virtual void SetEventCallback(std::function<void(Event&)> callback) override;

		virtual void* GetNativeWindow() override { return glfwWindow; }

	private:
		GLFWwindow* glfwWindow;
		WindowData data;
	};
}

