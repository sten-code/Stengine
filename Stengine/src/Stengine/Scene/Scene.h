#pragma once

#include "Stengine/Core/Timestep.h"
#include "Stengine/Renderer/EditorCamera.h"

#include <entt.hpp>

namespace Sten
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name);
		void DestroyEntity(Entity entity);

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

	template<typename T>
	inline void Scene::OnComponentAdded(Entity entity, T& component)
	{
		if constexpr (std::is_same_v<T, CameraComponent>)
		{
			dynamic_cast<CameraComponent&>(component).Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		}
	}
}