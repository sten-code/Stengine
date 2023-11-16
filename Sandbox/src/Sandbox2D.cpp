#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		std::chrono::time_point<std::chrono::steady_clock> endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		m_Func({m_Name, (end - start) * 0.001f });
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult result) { m_ProfileResults.push_back(result); })

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Sten::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sten::Timestep ts)
{
	PROFILE_SCOPE("Standbox2D::OnUpdate");

	m_Fps = 1.0f / ts;

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer Prep");
		Sten::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.18f, 1.0f });
		Sten::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Sten::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Sten::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_Color);
		Sten::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Sten::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);

		Sten::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
	ImGui::End();

	ImGui::Begin("FPS");
	ImGui::Text("%.2f", m_Fps);
	ImGui::End();

	ImGui::Begin("Profiler");
	for (ProfileResult& result : m_ProfileResults)
	{
		ImGui::Text("%.3fms %s", result.Time, result.Name);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Sten::Event& e)
{
	m_CameraController.OnEvent(e);
}
