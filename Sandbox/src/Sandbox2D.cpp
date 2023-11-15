#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_VertexArray = Sten::VertexArray::Create();

	float vertices[4 * 3] = {
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	   -0.5f,  0.5f, 0.0f
	};

	Sten::Ref<Sten::VertexBuffer> vertexBuffer = Sten::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Sten::ShaderDataType::Float3, "a_Position" }
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Sten::Ref<Sten::IndexBuffer> indexBuffer = Sten::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_ShaderLibrary.Load("color", "assets/shaders/Color.vert", "assets/shaders/Color.frag");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sten::Timestep ts)
{
	m_Fps = 1.0f / ts;
	m_CameraController.OnUpdate(ts);
	Sten::Ref<Sten::Shader> colorShader = m_ShaderLibrary.Get("color");

	Sten::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.18f, 1.0f });
	Sten::RenderCommand::Clear();

	Sten::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Sten::OpenGLShader>(colorShader)->Bind();
	std::dynamic_pointer_cast<Sten::OpenGLShader>(colorShader)->UploadUniformFloat4("u_Color", m_Color);

	Sten::Renderer::Submit(colorShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Sten::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
	ImGui::End();

	ImGui::Begin("FPS");
	ImGui::LabelText("FPS", "%.2f", m_Fps);
	ImGui::End();
}

void Sandbox2D::OnEvent(Sten::Event& e)
{
	m_CameraController.OnEvent(e);
}
