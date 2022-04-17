#include "StatsPanel.h"
#include <imgui.h>
#include <imgui_internal.h>

void Pixie::StatsPanel::OnImGuiRender()
{
	ImGui::Begin("Stats");
	std::string name = "None";
	if (hoveredEntity)
		name = hoveredEntity.GetComponent<TagComponent>().Tag;
	ImGui::Text("Hovered Entity: %s", name.c_str());
	ImGui::End();
}

void Pixie::StatsPanel::OnHooverEntity(Entity entity)
{
	hoveredEntity = entity;
}
