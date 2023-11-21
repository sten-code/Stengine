#pragma once

#include <Stengine.h>

#include "Panels/SceneHierarchyPanel.h"

namespace Sten
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_CameraController;
		
		Ref<Texture2D> m_Texture;
		Ref<VertexArray> m_VertexArray;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		float m_Fps = 0.0f;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}