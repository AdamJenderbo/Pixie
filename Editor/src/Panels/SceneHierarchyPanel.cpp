#include "SceneHierarchyPanel.h"

#include <imgui.h>

#include "Pixie/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp>

namespace Pixie 
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		this->context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		context->registry.each([&](auto entityID)
		{
			Entity entity{ entityID , context.get() };
			DrawEntityNode(entity);
		});

		// Om man klickar utanför entitet, deselecta nuvarande entitet
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectionContext = {};

		ImGui::End();

		ImGui::Begin("Properties");
		if (selectionContext)
			DrawComponents(selectionContext);

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		// Om man klickar på en entity, selecta den
		if (ImGui::IsItemClicked())
			selectionContext = entity;

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		// Rendarar alla komponenter i en entitet

		if (entity.HasComponent<TagComponent>())
		{
			auto& tagComponent = entity.GetComponent<TagComponent>();
			DrawTag(tagComponent);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transformComponent = entity.GetComponent<TransformComponent>();
			DrawTransform(transformComponent);
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			DrawCamera(cameraComponent);
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
			DrawSpriteRenderer(spriteRendererComponent);
		}
	}

	void SceneHierarchyPanel::DrawTag(TagComponent& tagComponent)
	{
		auto& tag = tagComponent.Tag;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer)); // Allokera minne
		strcpy_s(buffer, sizeof(buffer), tag.c_str()); // Kopiera tag till buffer

		if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			tag = std::string(buffer); // Skriv ändrat värde från buffer till tag
	}

	void SceneHierarchyPanel::DrawTransform(TransformComponent& transformComponent)
	{
		if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			auto& transform = transformComponent.Transform;
			ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawCamera(CameraComponent& cameraComponent)
	{
		if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
		{
			auto& camera = cameraComponent.Camera;

			ImGui::Checkbox("Primary", &cameraComponent.Primary);

			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
				if (ImGui::DragFloat("Vertical FOV", &verticalFov))
					camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));

				float orthoNear = camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near", &orthoNear))
					camera.SetPerspectiveNearClip(orthoNear);

				float orthoFar = camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far", &orthoFar))
					camera.SetPerspectiveFarClip(orthoFar);
			}

			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthoSize = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &orthoSize))
					camera.SetOrthographicSize(orthoSize);

				float orthoNear = camera.GetOrthographicNearClip();
				if (ImGui::DragFloat("Near", &orthoNear))
					camera.SetOrthographicNearClip(orthoNear);

				float orthoFar = camera.GetOrthographicFarClip();
				if (ImGui::DragFloat("Far", &orthoFar))
					camera.SetOrthographicFarClip(orthoFar);

				ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);
			}


			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawSpriteRenderer(SpriteRendererComponent& spriteRendererComponent)
	{
		if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(spriteRendererComponent.Color));
			ImGui::TreePop();
		}
	}
}