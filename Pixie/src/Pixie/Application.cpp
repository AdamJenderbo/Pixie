#include "pxpch.h"
#include "Application.h"
#include <iostream>
#include "Pixie/Renderer/Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pixie 
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::instance = nullptr;

	Application::Application(const std::string& name)
	{
		instance = this;

		window = Window::Create(WindowProps(name));
		window->SetEventCallback(PX_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		//imGuiLayer = new ImGuiLayer();
		//PushOverlay(imGuiLayer);
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			for (Layer* layer : layerStack)
				layer->OnUpdate(timestep);
			window->OnUpdate();

		};
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}