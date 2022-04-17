#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Scene.h"
#include "Pixie/Scene/Entity.h"
#include "Pixie/Scene/Components.h"

namespace Pixie
{

	class InspectorPanel
	{
	public:
		InspectorPanel() = default;

		void OnImGuiRender();

		void SetEntity(Entity entity);

	private:
		void DrawComponents(Entity& entity);

		static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

	private:
		Entity entity;
	};
}
