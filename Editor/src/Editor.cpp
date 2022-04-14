#include "Editor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Pixie/Scene/Components.h"

#include <imgui.h>

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

		auto entity = activeScene->CreateEntity("Green Square");
		entity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		greenSquare = entity;

		camera = activeScene->CreateEntity("Camera Entity");
		camera.AddComponent<CameraComponent>();

		secondaryCamera = activeScene->CreateEntity("Clip-Space Entity");
		auto& cc = secondaryCamera.AddComponent<CameraComponent>();
		cc.Primary = false;


		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& transform = GetComponent<TransformComponent>().Transform;
				transform[3][0] = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts)
			{
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KeyCode::A))
					transform[3][0] -= speed * ts;
				if (Input::IsKeyPressed(KeyCode::D))
					transform[3][0] += speed * ts;
				if (Input::IsKeyPressed(KeyCode::W))
					transform[3][1] += speed * ts;
				if (Input::IsKeyPressed(KeyCode::S))
					transform[3][1] -= speed * ts;
			}
		};

		camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		sceneHierarchyPanel.SetContext(activeScene);
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

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
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
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		sceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Inspector");

		if (greenSquare)
		{
			ImGui::Separator();
			auto& tag = greenSquare.GetComponent<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& squareColor = greenSquare.GetComponent<SpriteRendererComponent>().Color;
			ImGui::Separator();
		}

		ImGui::DragFloat3("Camera Transform",
			glm::value_ptr(camera.GetComponent<TransformComponent>().Transform[3]));

		if (ImGui::Checkbox("Camera A", &primaryCamera))
		{
			camera.GetComponent<CameraComponent>().Primary = primaryCamera;
			secondaryCamera.GetComponent<CameraComponent>().Primary = !primaryCamera;
		}

		{
			auto& camera = secondaryCamera.GetComponent<CameraComponent>().Camera;
			float orthoSize = camera.GetOrthographicSize();
			if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize))
				camera.SetOrthographicSize(orthoSize);
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");

		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewportFocused || !viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint32_t textureID = framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void Editor::OnEvent(Event& e)
	{
		cameraController.OnEvent(e);
	}

}