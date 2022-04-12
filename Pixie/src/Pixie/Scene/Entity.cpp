#include "pxpch.h"
#include "Entity.h"

namespace Pixie 
{

	Entity::Entity(entt::entity handle, Scene* scene)
		: entityHandle(handle), scene(scene)
	{
	}

}