#pragma once

#include <memory>

#ifdef TS_PLATFORM_WINDOWS
	#ifdef TS_DYNAMIC_LINK
		#ifdef TS_BUILD_DLL
			#define TASALY_API __declspec(dllexport)
		#else
			#define TASALY_API __declspec(dllimport)
		#endif // TS_BUILD_DLL
	#else
		#define TASALY_API
	#endif
#else
	#error Tasaly only support Windows!
#endif // TS_PLATFORM_WINDOWS

#ifdef TS_ENABLE_ASSERTS
	#define TS_ASSERT(x, ...)  { if(!(x)) { TS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TS_CORE_ASSERT(x, ...) { if(!(x)) { TS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TS_ASSERT(x, ...)
	#define TS_CORE_ASSERT(x, ...)
#endif // TS_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define TS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Tasaly {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
