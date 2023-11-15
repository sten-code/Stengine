#include <Stengine.h>
#include <Stengine/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class Sandbox : public Sten::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Sten::Application* Sten::CreateApplication()
{
	return new Sandbox();
}
