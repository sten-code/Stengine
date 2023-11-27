#pragma once

#ifdef ST_DEBUG
	// ------------- Settings --------------
	#define ST_ENABLE_ASSERTS
	//#define ST_PROFILE

	// ------------ Debug break ------------
	#if defined(ST_PLATFORM_WINDOWS)
		#define ST_DEBUGBREAK() __debugbreak()
	#elif defined(ST_PLATFORM_LINUX)
		#include <signal.h>
		#define ST_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak"
	#endif
#else
	#define ST_DEBUGBREAK()
#endif

#define ST_EXPAND_MACRO(x) x
#define ST_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)
#define ST_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include <memory>

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

#include "Stengine/Core/Log.h"
#include "Stengine/Core/Assert.h"