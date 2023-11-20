#include "stpch.h"
#include "Scene.h"

#include "Stengine/Renderer/Renderer2D.h"
#include "Stengine/Scene/Components.h"

#include <glm/glm.hpp>

namespace Sten
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}