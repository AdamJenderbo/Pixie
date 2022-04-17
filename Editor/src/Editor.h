#pragma once

#include "Pixie.h"
#include "Panels/ScenePanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"
#include "Panels/StatsPanel.h"

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

		void OnSelectEntity(Entity entity);
		void OnHooverEntity(Entity entity);
		void OnClickEntity(Entity entity);

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

		void SetActiveScene(Ref<Scene>& scene);

	private:

		Ref<Scene> activeScene;

		//EditorCamera editorCamera;
		//Ref<Framebuffer> framebuffer;

		//glm::vec2 viewportSize = { 0.0f, 0.0f };
		//glm::vec2 viewportBounds[2];
		//bool viewportFocused = false, viewportHovered = false;

		//int gizmoType = -1;

		//Entity hoveredEntity;

		// Panels
		ScenePanel scenePanel;
		SceneHierarchyPanel hierarchyPanel;
		InspectorPanel inspectorPanel;
		StatsPanel statsPanel;
	};
}