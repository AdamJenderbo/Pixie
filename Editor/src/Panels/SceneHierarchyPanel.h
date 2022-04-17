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

		void SetScene(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return selectedEntity; }
		void SelectEntity(Entity entity);
		void SetSelectEntityCallback(std::function<void(Entity)> callback);

	private:
		void DrawEntityNode(Entity entity);


	private:
		Ref<Scene> scene;
		Entity selectedEntity;
		std::function<void(Entity)> SelectEntityCallback;
	};
}
