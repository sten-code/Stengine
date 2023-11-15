#include "stpch.h"
#include "CameraController.h"

#include "Stengine/Core/Input.h"
#include "Stengine/Core/KeyCodes.h"

namespace Sten
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		// Camera Position
		glm::vec3 pos = m_Camera.GetPosition();
		if (Sten::Input::IsKeyPressed(ST_KEY_W)) pos.y += ts * m_CameraTranslationSpeed * m_ZoomLevel;
		if (Sten::Input::IsKeyPressed(ST_KEY_S)) pos.y -= ts * m_CameraTranslationSpeed * m_ZoomLevel;
		if (Sten::Input::IsKeyPressed(ST_KEY_A)) pos.x -= ts * m_CameraTranslationSpeed * m_ZoomLevel;
		if (Sten::Input::IsKeyPressed(ST_KEY_D)) pos.x += ts * m_CameraTranslationSpeed * m_ZoomLevel;
		m_Camera.SetPosition(pos);

		// Camera Rotation
		if (m_Rotation)
		{
			float rot = m_Camera.GetRotation();
			if (Sten::Input::IsKeyPressed(ST_KEY_LEFT))  rot += ts * m_CameraRotationSpeed;
			if (Sten::Input::IsKeyPressed(ST_KEY_RIGHT)) rot -= ts * m_CameraRotationSpeed;
			m_Camera.SetRotation(rot);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ST_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ST_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * m_CameraZoomSpeed * m_ZoomLevel;
		//m_ZoomLevel = std::max(m_ZoomLevel, 0.05f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	 
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}