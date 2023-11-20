#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	//Sten::Application::Get().GetWindow().SetVSync(true);
}

void Sandbox2D::OnAttach()
{
	ST_PROFILE_FUNCTION();

	m_Texture = Sten::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.02f;
	m_Particle.SizeVariation = 0.0f;
	m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 2.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 1.0f, 2.0f };
	m_Particle.Acceleration = { 0.0f, -3.0f };
	m_Particle.AccelerationVariation = { 0.0f, 0.0f };
	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Normalized = true;

	m_Tilemap = Sten::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");
}

void Sandbox2D::OnDetach()
{
	ST_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Sten::Timestep ts)
{
	ST_PROFILE_FUNCTION();

	m_Fps = 1.0f / ts;

	m_CameraController.OnUpdate(ts);

	Sten::Renderer2D::ResetStats();
	{
		ST_PROFILE_SCOPE("Renderer Prep");
		Sten::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.18f, 1.0f });
		Sten::RenderCommand::Clear();
	}
	
	{
		ST_PROFILE_SCOPE("Renderer Particles");

		if (Sten::Input::IsMouseButtonPressed(ST_MOUSE_BUTTON_LEFT))
		{
			glm::vec2 mouse = Sten::Input::GetMousePosition();
			uint32_t width = Sten::Application::Get().GetWindow().GetWidth();
			uint32_t height = Sten::Application::Get().GetWindow().GetHeight();

			Sten::OrthographicCameraBounds bounds = m_CameraController.GetCamera().GetBounds();
			glm::vec3 pos = m_CameraController.GetCamera().GetPosition();
			mouse.x = (mouse.x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			mouse.y = bounds.GetHeight() * 0.5f - (mouse.y / height) * bounds.GetHeight();
			m_Particle.Position = { mouse.x + pos.x, mouse.y + pos.y };
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}

		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Sten::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));

	ImGui::End();

	ImGui::Begin("FPS");
	ImGui::Text("%.2f", m_Fps);
	ImGui::End();
}

void Sandbox2D::OnEvent(Sten::Event& e)
{
	m_CameraController.OnEvent(e);
}
