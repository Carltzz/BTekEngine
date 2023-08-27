#include "GraphicsApi.h"

using namespace BTekEngine;

#ifdef _WIN32
#include "Graphics/Platform/MSWindow.h"
#include "Platform/OpenGLApiWindows.h"
GraphicsApi* BTekEngine::CreateGraphicsApi(void* windowBase, GraphicsApiType apiType) {
	MSWindow* msWindow = reinterpret_cast<MSWindow*>(windowBase);
	if (!msWindow) {
		return nullptr;
	}

	switch (apiType) {
	case GraphicsApiType::OpenGL:
		return new OpenGLApiWindows(msWindow->GetHWnd());
	default:
		return nullptr;
	}
}
#else
GraphicsApi* CreateGraphicsApi(void*, GraphicsApiType) {
	return nullptr;
}
#endif