#pragma once
#include "Util/Logger.h"

#if defined(_MSC_VER)
	#define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
	#define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#else
	#define EXPORT
	#define IMPORT
	#pragma warning Unsupported compiler
#endif

void* GetGraphicsApi();

extern "C" {
	EXPORT void InitialiseEngine();
	EXPORT void BTekLogMessage(BTekEngine::LogLevel level, const std::string& msg, ...);
}