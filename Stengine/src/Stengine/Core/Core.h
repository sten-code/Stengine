#pragma once

#if defined(_WIN64)
	#define ST_PLATFORM_WINDOWS
#elif defined(_WIN32)
	#error "x86 builds are not supported!"
#elif defined(__ANDROID__)
	#define ST_PLATFORM_ANDROID
	#error "Android not supported!"
#elif defined(__linux__)
	#define ST_PLATFROM_LINUX
	#error "Linux not supported!"
#elif defined(__APPLE__) || defined(__MACH__)
	#if TARGET_IPHONE_SIMPULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define ST_PLATFORM_IOS
		#error "IOS not supported!"
	#elif TARGET_OS_MAC == 1
		#define ST_PLATFORM_MACOS
		#error "MacOS not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#else
	#error "Unknown platform!"
#endif

#ifdef ST_DEBUG
	// ------------- Settings --------------
	#define ST_ENABLE_ASSERTS
	#define ST_PROFILE

	// ------------ Debug break ------------
	#if defined(ST_PLATFORM_WINDOWS)
		#define DEBUGBREAK() __debugbreak()
	#elif defined(ST_PLATFORM_LINUX)
		#include <signal.h>
		#define DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak"
	#endif
#else
	#define DEBUGBREAK()
#endif

#ifdef ST_ENABLE_ASSERTS
	#define ST_ASSERT(x, ...) { if (!(x)) { ST_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUGBREAK(); } }
	#define ST_CORE_ASSERT(x, ...) { if (!(x)) { ST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUGBREAK(); } }
#else
	#define ST_ASSERT(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

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