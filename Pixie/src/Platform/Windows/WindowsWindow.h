#pragma once

#include "Pixie/Window.h"

#include <GLFW/glfw3.h>

namespace Pixie {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.Width; }
		inline unsigned int GetHeight() const override { return data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual void* GetNativeWindow() const { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData data;
	};

}