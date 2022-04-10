#pragma once
#include "Event/Event.h"
#include <string>


namespace Pixie
{
	class Layer
	{
	public:
		Layer(std::string name);
		~Layer();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;

	private:
		std::string name;
	};
}