#pragma once

#include "Pixie/Base.h"
#include "Pixie/Events/KeyEvent.h"
#include "Pixie/Scene/Components.h"
#include "Pixie/Renderer/Framebuffer.h"

namespace Pixie
{
	class ScenePanel
	{
	public:
		ScenePanel();

		void SetScene(const Ref<Scene>& scene);
		void SetOnHooverEntity(std::function<void(Entity)> func);
		void SetOnClickEntity(std::function<void(Entity)> func);

		glm::vec2 GetViewportSize() { return viewportSize; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		void OnSelectEntity(Entity entity);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void OnImGuiRender();

	private:
		Ref<Scene> scene;
		std::function<void(Entity)> OnHooverEntity;
		std::function<void(Entity)> OnClickEntity;

		EditorCamera editorCamera;
		Ref<Framebuffer> framebuffer;

		glm::vec2 viewportSize = { 0.0f, 0.0f };
		glm::vec2 viewportBounds[2];
		bool viewportFocused = false, viewportHovered = false;

		Entity hoveredEntity;
		Entity selectedEntity;

		int gizmoType = -1;

		std::function<void(Entity)> OnHoveredEntity;
	};
}
