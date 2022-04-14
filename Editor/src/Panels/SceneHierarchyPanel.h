#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Scene.h"
#include "Pixie/Scene/Entity.h"
#include "Pixie/Scene/Components.h"

namespace Pixie 
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		void DrawTag(TagComponent& tagComponent);
		void DrawTransform(TransformComponent& transformComponent);
		void DrawCamera(CameraComponent& cameraComponent);
		void DrawSpriteRenderer(SpriteRendererComponent& spriteRendererComponent);


	private:
		Ref<Scene> context;
		Entity selectionContext;
	};

}
