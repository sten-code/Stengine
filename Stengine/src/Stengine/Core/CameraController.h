#pragma once

#include "Stengine/Core/Timestep.h"
#include "Stengine/Event/ApplicationEvent.h"
#include "Stengine/Event/Event.h"
#include "Stengine/Event/MouseEvent.h"
#include "Stengine/Renderer/Camera.h"

namespace Sten
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; };
		const OrthographicCamera& GetCamera() const { return m_Camera; };

		inline float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; CalculateView(); };
	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 50.0f;
		float m_CameraZoomSpeed = 0.25f;
	};
}