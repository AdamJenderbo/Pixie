#pragma once

#include "Pixie/Base.h"
#include "Pixie/Events/Event.h"
#include "Pixie/Timestep.h"

namespace Pixie
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Pixie::Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {};

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
	};
}