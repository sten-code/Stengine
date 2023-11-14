#include <Stengine.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public Sten::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, 1.6f, -0.9f, 0.9f), m_SquarePosition(0.0f)
	{
		m_VertexArray = Sten::VertexArray::Create();

		float vertices[3 * 7] = {
		   -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Sten::Ref<Sten::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Sten::VertexBuffer::Create(vertices, sizeof(vertices)));

		Sten::BufferLayout layout = {
			{ Sten::ShaderDataType::Float3, "a_Position" },
			{ Sten::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Sten::Ref<Sten::IndexBuffer> indexBuffer;
		indexBuffer.reset(Sten::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = // vertex shader
		R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
		
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = // fragment shader
		R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = Sten::Shader::CreateFromSource(vertexSrc, fragmentSrc);

		m_SquareVA = Sten::VertexArray::Create();

		float squareVertices[4 * 5] = {
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Sten::Ref<Sten::VertexBuffer> squareVB;
		squareVB.reset(Sten::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Sten::ShaderDataType::Float3, "a_Position" },
			{ Sten::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Sten::Ref<Sten::IndexBuffer> squareIB;
		squareIB.reset(Sten::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string colorVertexSrc = // vertex shader
		R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
		
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string colorFragmentSrc = // fragment shader
		R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_ColorShader = Sten::Shader::CreateFromSource(colorVertexSrc, colorFragmentSrc);

		m_TextureShader = Sten::Shader::Create("assets/shaders/Texture.vert", "assets/shaders/Texture.frag");

		m_Texture = Sten::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Sten::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Sten::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Sten::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Sten::Timestep ts) override
	{
		Sten::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.18f, 1.0f });
		Sten::RenderCommand::Clear();

		// Camera Position
		glm::vec3 pos = m_Camera.GetPosition();
		if (Sten::Input::IsKeyPressed(ST_KEY_W)) pos.y += ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_S)) pos.y -= ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_A)) pos.x -= ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_D)) pos.x += ts;
		m_Camera.SetPosition(pos);

		// Camera Rotation
		float rot = m_Camera.GetRotation();
		if (Sten::Input::IsKeyPressed(ST_KEY_LEFT))  rot += 50.0f * ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_RIGHT)) rot -= 50.0f * ts;
		m_Camera.SetRotation(rot);

		// Square Position
		if (Sten::Input::IsKeyPressed(ST_KEY_I)) m_SquarePosition.y += ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_K)) m_SquarePosition.y -= ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_J)) m_SquarePosition.x -= ts;
		if (Sten::Input::IsKeyPressed(ST_KEY_L)) m_SquarePosition.x += ts;

		Sten::Renderer::BeginScene(m_Camera);

		static glm::mat4 squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sten::OpenGLShader>(m_ColorShader)->Bind();
		std::dynamic_pointer_cast<Sten::OpenGLShader>(m_ColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
				Sten::Renderer::Submit(m_ColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Sten::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Sten::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangle
		//Sten::Renderer::Submit(m_Shader, m_VertexArray);

		Sten::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Sten::Event& event) override
	{

	}
private:
	Sten::Ref<Sten::Shader> m_Shader;
	Sten::Ref<Sten::VertexArray> m_VertexArray;

	Sten::Ref<Sten::Shader> m_ColorShader, m_TextureShader;
	Sten::Ref<Sten::VertexArray> m_SquareVA;

	Sten::Ref<Sten::Texture2D> m_Texture, m_ChernoLogoTexture;

	Sten::OrthographicCamera m_Camera;

	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Sten::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Sten::Application* Sten::CreateApplication()
{
	return new Sandbox();
}
