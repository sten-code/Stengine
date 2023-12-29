#include "stpch.h"
#include "Stengine/Core/Window.h"
#include "Stengine/Core/Core.h"

#ifdef ST_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif
#ifdef ST_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#endif

namespace Sten
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef ST_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			#ifdef ST_PLATFORM_LINUX
				return CreateScope<LinuxWindow>(props);
			#else
				ST_CORE_ASSERT(false, "Unknown platform!");
				return nullptr;
			#endif
		#endif
	}

}