#include <Stengine.h>

class Sandbox : public Sten::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Sten::Application* Sten::CreateApplication()
{
	return new Sandbox();
}
