#pragma once

#include "Pixie/Base.h"

#include "Pixie/Console.h"
#include "Pixie/Window.h"
#include "Pixie/LayerStack.h"
#include "Pixie/Events/Event.h"
#include "Pixie/Events/ApplicationEvent.h"

#include "Pixie/Timestep.h"

#include "Pixie/ImGui/ImGuiLayer.h"



namespace Pixie 
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			if (index >= Count) Console::LogError("Command Line Args error");
			return Args[index];
		}
	};

	class Application
	{
	public:
		Application(const std::string& name = "Pixie App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return imGuiLayer; }

		static Application& Get() { return *instance; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return commandLineArgs; }

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationCommandLineArgs commandLineArgs;
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