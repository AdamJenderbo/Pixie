#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Scene.h"
#include "Pixie/Scene/Entity.h"

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
	private:
		Ref<Scene> context;
		Entity selectionContext;
	};

}
