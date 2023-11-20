#include <Stengine.h>
#include <Stengine/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class Steditor : public Sten::Application
{
public:
	Steditor()
	{
		PushLayer(new Sandbox2D());
	}

	~Steditor()
	{
	}
};

Sten::Application* Sten::CreateApplication()
{
	return new Steditor();
}
