#pragma once

#include "Scene.h"
#include "Pixie/Console.h"

namespace Pixie 
{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if(HasComponent<T>()) 
				Console::LogError("Entity already has component!");
			return scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if(!HasComponent<T>()) 
				Console::LogError("Entity does not have component!");
			return scene->registry.get<T>(entityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return scene->registry.all_of<T>(entityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			if(!HasComponent<T>()) Console::LogError("Entity does not have component!");
			scene->registry.remove<T>(entityHandle);
		}

		int GetHandle() { return (int) entityHandle; }

		operator bool() const { return entityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)entityHandle; }

		bool operator==(const Entity& other) const
		{
			return entityHandle == other.entityHandle && scene == other.scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity entityHandle{ entt::null };
		Scene* scene = nullptr;
	};

}