#pragma once

#ifdef ST_PLATFORM_WINDOWS
	#ifdef ST_BUILD_DLL
		#define STEN_API __declspec(dllexport)
	#else
		#define STEN_API __declspec(dllimport)
	#endif
#else
	#error Stengine only supports Windows!
#endif
