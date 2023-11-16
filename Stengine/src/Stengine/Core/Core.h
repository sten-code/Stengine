#pragma once
#include <memory>

#ifdef ST_PLATFORM_WINDOWS
	#if ST_DYNAMIC_LINK
		#ifdef ST_BUILD_DLL
			#define STEN_API __declspec(dllexport)
		#else
			#define STEN_API __declspec(dllimport)
		#endif
	#else
		#define STEN_API
	#endif
#else
	#error Stengine only supports Windows!
#endif

#ifdef ST_DEBUG
	#define ST_ENABLE_ASSERTS
#endif

#ifdef ST_ENABLE_ASSERTS
	#define _assert(x, ...) { if (!(x)) { _error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ST_CORE_ASSERT(x, ...) { if (!(x)) { ST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define _assert(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ST_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sten
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}