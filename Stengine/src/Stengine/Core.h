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

#ifdef ST_ENABLE_ASSERTS
	#define _assert(x, ...) { if (!(x)) { _error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ST_CORE_ASSERT(x, ...) { if (!(x)) { ST_CORE_ASSERT("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define _assert(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ST_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
