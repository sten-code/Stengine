#include <Stengine.h>

class ExampleLayer : public Sten::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{}

	void OnUpdate() override
	{
		_info("ExampleLayer::Update");
	}

	void OnEvent(Sten::Event& event) override
	{
		_trace("{0}", event);
	}
};

class Sandbox : public Sten::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushOverlay(new Sten::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Sten::Application* Sten::CreateApplication()
{
	return new Sandbox();
}
