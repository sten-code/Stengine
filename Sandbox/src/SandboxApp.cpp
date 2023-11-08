#include <Stengine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Sten::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{}

	void OnUpdate() override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("test");
		ImGui::Text("test text");
		ImGui::End();
	}

	void OnEvent(Sten::Event& event) override
	{

	}
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
