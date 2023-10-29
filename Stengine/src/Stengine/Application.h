#pragma once

#include "Core.h"

namespace Sten
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
