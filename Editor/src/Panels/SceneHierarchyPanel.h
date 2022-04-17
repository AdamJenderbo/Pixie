#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Components.h"

namespace Pixie 
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetScene(const Ref<Scene>& scene);
		void SetOnSelectEntity(std::function<void(Entity)> func);

		void OnImGuiRender();
		void OnClickEntity(Entity entity);

	private:
		void SelectEntity(Entity entity);
		void DrawEntityNode(Entity entity);


	private:
		Ref<Scene> scene;
		Entity selectedEntity;
		std::function<void(Entity)> OnSelectEntity;
	};
}
