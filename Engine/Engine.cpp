#include "Engine.h"
#include "Core/MSWindow.h"
#include <iostream>

Window* InitPlatform();

void InitialiseEngine() {
	Window* window = InitPlatform();
	window->Run();
	delete window;
}

#ifdef _WIN32
Window* InitPlatform() {
	BTekEngine::RegisterWindowClass();
	return new BTekEngine::MSWindow("BTeKEngine", 1280, 720);
}
#else
Window* InitPlatform() {
	// TODO: Output that this platform is not supported
	return NULL;
}
#endif