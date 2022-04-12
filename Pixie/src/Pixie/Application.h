#pragma once

#include "Pixie/Base.h"

#include "Pixie/Window.h"
#include "Pixie/LayerStack.h"
#include "Pixie/Events/Event.h"
#include "Pixie/Events/ApplicationEvent.h"

#include "Pixie/Timestep.h"

#include "Pixie/ImGui/ImGuiLayer.h"


namespace Pixie 
{

	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *window; }

		void Close();

		static Application& Get() { return *instance; }
		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		bool minimized = false;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;
	private:
		static Application* instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}