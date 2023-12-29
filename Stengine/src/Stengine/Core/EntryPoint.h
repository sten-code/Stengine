#pragma once
#include "Stengine/Core/Core.h"
#include "Stengine/Core/Application.h"

extern Sten::Application* Sten::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	ST_PROFILE_BEGIN_SESSION("Startup", "StengineProfile-Startup.json");
	Sten::Log::Init();
	Sten::Application* app = Sten::CreateApplication({ argc, argv });
	ST_PROFILE_END_SESSION();

	ST_PROFILE_BEGIN_SESSION("Runtime", "StengineProfile-Runtime.json");
	app->Run();
	ST_PROFILE_END_SESSION();

	ST_PROFILE_BEGIN_SESSION("Shutdown", "StengineProfile-Shutdown.json");
	delete app;
	ST_PROFILE_END_SESSION();

	return 0;
}
