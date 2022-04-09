#pragma once
#include "Window.h"

namespace Pixie
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	protected:
		virtual void Update() = 0;
	private:
		Window* window;
	};
}