#pragma once

#ifdef MTL_PLATFORM_WINDOWS
	#ifdef MTL_BUILD_DLL
		#define MEWTLE_API __declspec(dllexport)
	#else
		#define MEWTLE_API __declspec(dllimport)
	#endif
#else
	#error Mewtle only supports Windows.
#endif