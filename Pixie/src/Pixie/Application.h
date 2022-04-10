#pragma once
#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"

namespace Pixie
{
	class Application
	{
	public:
		Application();
		~Application();

		void PushLayer(Layer* layer);

		void Run();

		void OnEvent(Event& e);

		Window& GetWindow() { return *window; }

		static Application& Get() { return *instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		bool running = false;
		Window* window;
		LayerStack layerStack;

		static Application* instance;
	};
}