#pragma once

#include "Pixie/Layer.h"

#include "Pixie/Events/ApplicationEvent.h"
#include "Pixie/Events/KeyEvent.h"
#include "Pixie/Events/MouseEvent.h"

namespace Pixie 
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { blockEvents = block; }
	private:
		bool blockEvents = true;
		float time = 0.0f;
	};

}