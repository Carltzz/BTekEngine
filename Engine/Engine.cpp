#include "Engine.h"
#include <iostream>
#include "Graphics/Platform/Window.h"
#include "Util/ConsoleLogger.h"

using namespace BTekEngine;

ConsoleLogger* logger;
Window* window;
GraphicsApi* api;

void BTekLogMessage(LogLevel logLevel, const std::string& msg, ...) {
	logger->Log(logLevel, std::string(msg));
}

void InitialiseDebugging() {
	logger = new ConsoleLogger();
	BTekLogMessage(LogLevel::INFO, "Initialised the logger");
}

#ifdef _WIN32
#include "Graphics/Platform/MSWindow.h"
void InitPlatform() {
	BTekEngine::RegisterWindowClass();
	window = new BTekEngine::MSWindow(GraphicsApiType::OpenGL, "BTeKEngine", 1280, 720);
	api = window->GetGraphicsApi();
	api->LoadCoreShaders();
	BTekLogMessage(LogLevel::INFO, "Initialised platform (using windows)");
}
#else
Window* InitPlatform() {
	// TODO: Output that this platform is not supported
	return NULL;
}
#endif

void Start() {
	window->Run();
}

void CleanUp() {
	delete window;
	delete logger;
}

void InitialiseEngine() {
	InitialiseDebugging();
	InitPlatform();
	Start();
	CleanUp();
}

void* GetGraphicsApi() {
	return api;
}