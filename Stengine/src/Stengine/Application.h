#pragma once

#include "Core.h"

namespace sten
{
	class STEN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
