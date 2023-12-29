#pragma once

#include "Stengine/Core/UUID.h"
#include "Stengine/Scene/Components.h"
#include "Stengine/Scene/Scene.h"

#include <entt.hpp>

namespace Sten
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ST_CORE_ASSERT(!HasComponent<T>(), "Entity already has that component.");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			ST_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have that component.");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			ST_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have that component.");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		
		UUID GetUUID() { return GetComponent<IDComponent>().Id; }
		TransformComponent GetTransform() { return GetComponent<TransformComponent>(); }
		std::string GetName() { return GetComponent<TagComponent>().Tag; }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;

		friend class SceneSerializer;
	};
}