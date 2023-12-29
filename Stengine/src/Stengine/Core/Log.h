#pragma once

#include "Stengine/Core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <memory>

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)


namespace Sten
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternio)
{
	return os << glm::to_string(quaternio);
}

#define ST_CORE_TRACE(...)     ::Sten::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ST_CORE_INFO(...)      ::Sten::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ST_CORE_WARN(...)      ::Sten::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ST_CORE_ERROR(...)     ::Sten::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ST_CORE_CRITICAL(...)  ::Sten::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ST_TRACE(...)		   ::Sten::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ST_INFO(...)		   ::Sten::Log::GetClientLogger()->info(__VA_ARGS__)
#define ST_WARN(...)		   ::Sten::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ST_ERROR(...)		   ::Sten::Log::GetClientLogger()->error(__VA_ARGS__)
#define ST_CRITICAL(...)	   ::Sten::Log::GetClientLogger()->critical(__VA_ARGS__)
