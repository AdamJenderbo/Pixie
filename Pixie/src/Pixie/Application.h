#pragma once
#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

namespace Pixie
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		Window& GetWindow() { return *window; }

		static Application& Get() { return *instance; }

	protected:
		virtual void OnUpdate() = 0;

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Window* window;
		bool running = false;

		static Application* instance;
	};
}