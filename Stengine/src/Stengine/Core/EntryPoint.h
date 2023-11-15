#pragma once

#ifdef ST_PLATFORM_WINDOWS

extern Sten::Application* Sten::CreateApplication();

int main(int argc, char** argv)
{
	Sten::Log::Init();
	ST_CORE_TRACE("Initialized Stengine");

	Sten::Application* app = Sten::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#else
	#error Stengine only supports Windows!
#endif
