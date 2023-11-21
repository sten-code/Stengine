#include "stpch.h"
#include "Entity.h"

namespace Sten
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}