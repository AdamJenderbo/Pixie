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
		void SetSelectedEntity(Entity entity);

	private:
		void DrawEntityNode(Entity entity);

		void DrawComponents(Entity& entity);

		static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);


	private:
		Ref<Scene> scene;
		Entity selectedEntity;
		std::function<void(Ref<Entity>)> SelectEntityCallback;
	};
}
