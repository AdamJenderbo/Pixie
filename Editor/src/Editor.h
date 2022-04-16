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
		Ref<Scene> activeScene;
		Ref<Framebuffer> framebuffer;
		OrthographicCameraController cameraController;
		Entity greenSquare;
		Entity blueSquare;
		Entity camera;
		Entity secondaryCamera;
		bool primaryCamera = true;

		Ref<Texture2D> texture;

		glm::vec2 viewportSize = { 0.0f, 0.0f };
		bool viewportFocused = false, viewportHovered = false;

		SceneHierarchyPanel sceneHierarchyPanel;
		int gizmoType = -1;
	};

}