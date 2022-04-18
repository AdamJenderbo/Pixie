#pragma once
#include "Pixie.h"
#include "Pixie/Scene/Entity.h"
#include "Pixie/Renderer/Framebuffer.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

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
		void OnEvent(Event & e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent & e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent & e);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path & path);
		void SaveSceneAs();
	private:
		Ref<Scene> scene;
		EditorCamera editorCamera;
		Ref<Framebuffer> framebuffer;

		bool viewportFocused = false, viewportHovered = false;
		glm::vec2 viewportSize = { 0.0f, 0.0f };
		glm::vec2 viewportBounds[2];

		Entity hoveredEntity;

		int gizmoType = -1;

		// Panels
		HierarchyPanel hierarchyPanel;
		ContentBrowserPanel contentBrowserPanel;

	};
}