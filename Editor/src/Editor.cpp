#include "Editor.h"

#include "Pixie/Scene/Components.h"
#include "Pixie/Scene/SceneSerializer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Pixie/ImGui/ImGuizmo.h"

#include "Pixie/Math/Math.h"

#include "Pixie/Utils/PlatformUtils.h"

#define PX_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Pixie
{

	Editor::Editor()
		: Layer("EditorLayer")
	{
	}

	void Editor::OnAttach()
	{
		//FramebufferSpecification fbSpec;
		//fbSpec.Attachments = { 
		//	FramebufferTextureFormat::RGBA8, 
		//	FramebufferTextureFormat::RED_INTEGER, 
		//	//FramebufferTextureFormat::Depth
		//};
		//fbSpec.Width = 1280;
		//fbSpec.Height = 720;
		//framebuffer = Framebuffer::Create(fbSpec);

		SetActiveScene(std::make_shared<Scene>());

		scenePanel.SetOnHooverEntity(PX_BIND_EVENT_FN(Editor::OnHooverEntity));
		scenePanel.SetOnClickEntity(PX_BIND_EVENT_FN(Editor::OnClickEntity));

		hierarchyPanel.SetOnSelectEntity(PX_BIND_EVENT_FN(Editor::OnSelectEntity));
	}

	void Editor::OnDetach()
	{
	}

	void Editor::OnUpdate(Timestep ts)
	{
		scenePanel.OnUpdate(ts);
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

		scenePanel.OnImGuiRender();
		hierarchyPanel.OnImGuiRender();
		inspectorPanel.OnImGuiRender();
		statsPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::PopStyleVar();
		ImGui::End();
	}

	void Editor::OnEvent(Event& e)
	{
		scenePanel.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(PX_BIND_EVENT_FN(Editor::OnKeyPressed));
	}

	void Editor::OnSelectEntity(Entity entity)
	{
		scenePanel.OnSelectEntity(entity);
		inspectorPanel.OnSelectEntity(entity);
	}

	void Editor::OnHooverEntity(Entity entity)
	{
		statsPanel.OnHooverEntity(entity);
	}

	void Editor::OnClickEntity(Entity entity)
	{
		hierarchyPanel.OnClickEntity(entity);
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
		}
	}

	void Editor::NewScene()
	{
		SetActiveScene(std::make_shared<Scene>());
		activeScene->OnViewportResize((uint32_t)scenePanel.GetViewportSize().x, (uint32_t)scenePanel.GetViewportSize().y);
	}

	void Editor::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Pixie Scene (*.pixie)\0*.pixie\0");
		if (!filepath.empty())
		{
			SetActiveScene(std::make_shared<Scene>());
			activeScene->OnViewportResize((uint32_t)scenePanel.GetViewportSize().x, (uint32_t)scenePanel.GetViewportSize().y);

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
	void Editor::SetActiveScene(Ref<Scene>& scene)
	{
		activeScene = scene;
		scenePanel.SetScene(scene);
		hierarchyPanel.SetScene(scene);
	}
}