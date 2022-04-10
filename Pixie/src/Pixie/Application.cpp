#include "Application.h"
#include "Console.h"
#include "Event/ApplicationEvent.h"

namespace Pixie
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
		: running(false)
	{
		window = Window::Create(640, 480, "Pixie Engine");
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::Run()
	{
		running = true;
		while (running)
		{
			OnUpdate();
			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		Event::Handle<WindowCloseEvent>(e, BIND_EVENT_FN(OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}

