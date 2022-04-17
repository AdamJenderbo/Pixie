#pragma once

#include "Pixie/Base.h"
#include "Pixie/Scene/Scene.h"
#include "Pixie/Scene/Entity.h"
#include "Pixie/Scene/Components.h"

namespace Pixie
{
	class StatsPanel
	{
	public:
		StatsPanel() = default;

		void OnImGuiRender();
		void OnHooverEntity(Entity entity);

	private:
		Entity hoveredEntity;
	};
}
