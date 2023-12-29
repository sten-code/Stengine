#pragma once

#include "Stengine/Core/Timestep.h"
#include "Stengine/Core/UUID.h"
#include "Stengine/Renderer/EditorCamera.h"

#include <box2d/box2d.h>
#include <entt.hpp>

namespace Sten
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name, UUID uuid = UUID());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DuplicateEntity(Entity entity);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

	template<typename T>
	inline void Scene::OnComponentAdded(Entity entity, T& component)
	{
		if constexpr (std::is_same_v<T, CameraComponent>)
		{
			if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
				dynamic_cast<CameraComponent&>(component).Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		}
	}
}