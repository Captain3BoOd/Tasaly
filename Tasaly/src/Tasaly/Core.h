#pragma once

#ifdef TS_PLATFORM_WINDOWS
	#ifdef TS_BUILD_DLL
		#define TASALY_API __declspec(dllexport)
	#else
		#define TASALY_API __declspec(dllimport)
	#endif // TS_BUILD_DLL
#else
	#error Tasaly only support Windows!
#endif // TS_PLATFORM_WINDOWS

