#include "Application.h"
#include "Console.h"
#include "Event/ApplicationEvent.h"

namespace Pixie
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;

		window = Window::Create(640, 480, "Pixie Engine");
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::Run()
	{
		running = true;
		while (running)
		{
			for (Layer* layer : layerStack)
				layer->OnUpdate();

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		Event::Handle<WindowCloseEvent>(e, BIND_EVENT_FN(OnWindowClose));

		for (Layer* layer : layerStack)
			layer->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}

