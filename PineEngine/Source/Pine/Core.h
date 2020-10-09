#pragma once
#include "Core.h"

#ifdef PINE_PLATFORM_WINDOWS
	#ifdef PINE_BUILD_DLL
		#define PINE_API __declspec(dllexport)
	#else
		#define PINE_API __declspec(dllimport)
	#endif

#else
#error Pine currently only supports Windows!
#endif