#pragma once

#ifdef ST_PLATFORM_WINDOWS

extern sten::Application* sten::CreateApplication();

int main(int argc, char** argv)
{
	sten::Application* app = sten::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#else
	#error Stengine only supports Windows!
#endif
