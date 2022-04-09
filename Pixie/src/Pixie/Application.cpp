#include "Application.h"
#include "Console.h"

namespace Pixie
{
	Application::Application()
	{
		window = Window::Create(640, 480, "Pixie Engine");
		Console::Log("App");
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::Run()
	{
		while (true)
		{
			Update();
			window->Update();
		}
	}
}

