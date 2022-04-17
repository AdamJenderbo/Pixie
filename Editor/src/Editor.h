#pragma once

#include "Pixie.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Pixie
{
	class Editor : public Layer
	{
	public:
		Editor();
		virtual ~Editor() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:

		EditorCamera editorCamera;
		Ref<Scene> activeScene;
		Ref<Framebuffer> framebuffer;

		glm::vec2 viewportSize = { 0.0f, 0.0f };
		glm::vec2 viewportBounds[2];
		bool viewportFocused = false, viewportHovered = false;

		int gizmoType = -1;

		Entity hoveredEntity;

		// Panels
		SceneHierarchyPanel sceneHierarchyPanel;
	};

}