#pragma once
#include "entt/entt.hpp"
#include "Pixie/Timestep.h"
#include "Pixie/Renderer/EditorCamera.h"


namespace Pixie
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetMainCameraEntity();


	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void UpdateScripts(Timestep ts);

	
	private:
		entt::registry registry;
		uint32_t viewportWidth = 0, viewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class HierarchyPanel;
	};
}