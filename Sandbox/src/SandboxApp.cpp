#include <Stengine.h>

class Sandbox : public sten::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

sten::Application* sten::CreateApplication()
{
	return new Sandbox();
}