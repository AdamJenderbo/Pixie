#include "Editor.h"

#include "Pixie/Scene/Components.h"
#include "Pixie/Scene/SceneSerializer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Pixie/ImGui/ImGuizmo.h"

#include "Pixie/Math/Math.h"

#include "Pixie/Utils/PlatformUtils.h"

namespace Pixie
{

	Editor::Editor()
		: Layer("EditorLayer"), cameraController(1280.0f / 720.0f)
	{
	}

	void Editor::OnAttach()
	{
		texture = Texture2D::Create("assets/textures/mario.png");

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		framebuffer = Framebuffer::Create(fbSpec);

		activeScene = std::make_shared<Scene>();;

		//auto greenSquare = activeScene->CreateEntity("Green Square");
		//greenSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		//auto redSquare = activeScene->CreateEntity("Red Square");
		//redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		camera = activeScene->CreateEntity("Camera");
		camera.AddComponent<CameraComponent>();

		class CameraController : public ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(Timestep ts) override
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::J))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::L))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(Key::I))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::K))
					translation.y -= speed * ts;
			}
		};

		camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		sceneHierarchyPanel.SetScene(activeScene);
	}

	void Editor::OnDetach()
	{
	}

	void Editor::OnUpdate(Timestep ts)
	{

		// Resize
		FramebufferSpecification spec = framebuffer->GetSpecification();
		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
			(spec.Width != viewportSize.x || spec.Height != viewportSize.y))
		{
			framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			cameraController.OnResize(viewportSize.x, viewportSize.y);

			activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}

		// Update
		//if (viewportFocused)
		//	cameraController.OnUpdate(ts);

		// Render
		framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.08f, 0.08f, 0.08f, 1 });
		RenderCommand::Clear();

		activeScene->OnUpdate(ts);

		framebuffer->Unbind();
	}

	void Editor::OnImGuiRender()
	{
		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		sceneHierarchyPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");

		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewportFocused && !viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint32_t textureID = framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Gizmos
		Entity selectedEntity = sceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && gizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			// Camera
			auto cameraEntity = activeScene->GetMainCameraEntity();
			const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			const glm::mat4& cameraProjection = camera.GetProjection();
			glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

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
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void Editor::OnEvent(Event& e)
	{
		cameraController.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(PX_BIND_EVENT_FN(Editor::OnKeyPressed));
	}

	bool Editor::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
		case Key::N:
		{
			if (control)
				NewScene();

			break;
		}
		case Key::O:
		{
			if (control)
				OpenScene();

			break;
		}
		case Key::S:
		{
			if (control && shift)
				SaveSceneAs();

			break;
		}

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

	void Editor::NewScene()
	{
		activeScene = std::make_shared<Scene>();
		activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		sceneHierarchyPanel.SetScene(activeScene);
	}

	void Editor::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Pixie Scene (*.pixie)\0*.pixie\0");
		if (!filepath.empty())
		{
			activeScene = std::make_shared<Scene>();
			activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			sceneHierarchyPanel.SetScene(activeScene);

			SceneSerializer serializer(activeScene);

			serializer.Deserialize(filepath);
			class CameraController : public ScriptableEntity
			{
			public:
				virtual void OnCreate() override
				{
				}

				virtual void OnDestroy() override
				{
				}

				virtual void OnUpdate(Timestep ts) override
				{
					auto& translation = GetComponent<TransformComponent>().Translation;
					float speed = 5.0f;

					if (Input::IsKeyPressed(Key::Left))
						translation.x -= speed * ts;
					if (Input::IsKeyPressed(Key::Right))
						translation.x += speed * ts;
					if (Input::IsKeyPressed(Key::Up))
						translation.y += speed * ts;
					if (Input::IsKeyPressed(Key::Down))
						translation.y -= speed * ts;
				}
			};

			activeScene->GetMainCameraEntity().AddComponent<NativeScriptComponent>().Bind<CameraController>();
		}
	}

	void Editor::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Pixie Scene (*.pixie)\0*.pixie\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(activeScene);
			serializer.Serialize(filepath);
		}
	}
}