#include <Stengine.h>
#include <Stengine/Core/EntryPoint.h>

#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace Sten
{
	class Steditor : public Application
	{
	public:
		Steditor(ApplicationCommandLineArgs args)
			: Application(WindowProps("Steditor", 1280, 720), args)
		{
			PushLayer(new EditorLayer());
		}

		~Steditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Steditor(args);
	}
}