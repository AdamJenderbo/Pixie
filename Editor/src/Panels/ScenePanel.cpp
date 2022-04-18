#include "ScenePanel.h"
#include "Pixie.h"
#include "Pixie/Base.h"
#include "Pixie/Application.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Pixie/ImGui/ImGuizmo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Pixie/Math/Math.h"

namespace Pixie
{
	ScenePanel::ScenePanel()
	{
		FramebufferSpecification fbSpec;
		fbSpec.Attachments = {
			FramebufferTextureFormat::RGBA8,
			FramebufferTextureFormat::RED_INTEGER,
			//FramebufferTextureFormat::Depth
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		framebuffer = Framebuffer::Create(fbSpec);

		editorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
	}

	void ScenePanel::SetScene(const Ref<Scene>& scene)
	{
		this->scene = scene;
	}

	void ScenePanel::SetOnHooverEntity(std::function<void(Entity)> func)
	{
		OnHooverEntity = func;
	}

	void ScenePanel::SetOnClickEntity(std::function<void(Entity)> func)
	{
		OnClickEntity = func;
	}


	void ScenePanel::OnUpdate(Timestep ts)
	{
		FramebufferSpecification spec = framebuffer->GetSpecification();
		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
			(spec.Width != viewportSize.x || spec.Height != viewportSize.y))
		{
			framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			editorCamera.SetViewportSize(viewportSize.x, viewportSize.y);
			scene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}

		editorCamera.OnUpdate(ts);

		framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.08f, 0.08f, 0.08f, 1 });
		RenderCommand::Clear();

		framebuffer->ClearAttachment(1, -1);

		scene->OnUpdateEditor(ts, editorCamera);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= viewportBounds[0].x;
		my -= viewportBounds[0].y;
		glm::vec2 viewportSize = viewportBounds[1] - viewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = framebuffer->ReadPixel(1, mouseX, mouseY);
			hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, scene.get());
			OnHooverEntity(hoveredEntity);
		}

		framebuffer->Unbind();
	}

	void ScenePanel::OnEvent(Event& e)
	{
		editorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(PX_BIND_EVENT_FN(ScenePanel::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(PX_BIND_EVENT_FN(ScenePanel::OnMouseButtonPressed));
	}

	bool ScenePanel::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		switch (e.GetKeyCode())
		{
		// Gizmos
		case Key::Q:
			gizmoType = -1;
			break;
		case Key::W:
			gizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case Key::E:
			gizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case Key::R:
			gizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

	void ScenePanel::OnSelectEntity(Entity entity)
	{
		selectedEntity = entity;
	}

	bool ScenePanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if (viewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				OnClickEntity(hoveredEntity);
		}
		return false;
	}

	void ScenePanel::OnImGuiRender()
	{
		ImGui::Begin("Scene");

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewportFocused && !viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Gizmos
		if (selectedEntity && gizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(viewportBounds[0].x, viewportBounds[0].y, viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y);

			// Runtime camera from entity
			//auto cameraEntity = activeScene->GetMainCameraEntity();
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			//const glm::mat4& cameraProjection = camera.GetProjection();
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor camera
			const glm::mat4& cameraProjection = editorCamera.GetProjection();
			glm::mat4 cameraView = editorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (gizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();
	}
}


