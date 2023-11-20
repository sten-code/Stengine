#include <Stengine.h>
#include <Stengine/Core/EntryPoint.h>

#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

namespace Sten
{
	class Steditor : public Application
	{
	public:
		Steditor()
			: Application(WindowProps("Steditor", 1280, 720))
		{
			PushLayer(new EditorLayer());
		}

		~Steditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Steditor();
	}
}