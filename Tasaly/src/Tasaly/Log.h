#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Tasaly {

	class TASALY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}

// Core log macros
#define TS_CORE_TRACE(...)    ::Tasaly::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TS_CORE_INFO(...)     ::Tasaly::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TS_CORE_WARN(...)     ::Tasaly::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TS_CORE_ERROR(...)    ::Tasaly::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TS_CORE_FATAL(...)    ::Tasaly::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TS_TRACE(...)         ::Tasaly::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TS_INFO(...)          ::Tasaly::Log::GetClientLogger()->info(__VA_ARGS__)
#define TS_WARN(...)          ::Tasaly::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TS_ERROR(...)         ::Tasaly::Log::GetClientLogger()->error(__VA_ARGS__)
#define TS_FATAL(...)         ::Tasaly::Log::GetClientLogger()->fatal(__VA_ARGS__)
