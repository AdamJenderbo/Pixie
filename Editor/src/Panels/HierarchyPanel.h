#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Components.h"

namespace Pixie 
{
	class HierarchyPanel
	{
	public:
		HierarchyPanel() = default;
		HierarchyPanel(const Ref<Scene>&scene);

		void SetScene(const Ref<Scene>&scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return selectedEntity; }
		void SetSelectedEntity(Entity entity);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> scene;
		Entity selectedEntity;
	};
}
