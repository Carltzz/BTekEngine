#include "GraphicsApi.h"
#include <map>

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

const std::map<BTekEngine::ShaderPrimitiveType, int> shader_var_sizes = {
	{BTekEngine::ShaderPrimitiveType::FLOAT, 4},
	{BTekEngine::ShaderPrimitiveType::VEC2F, 8},
	{BTekEngine::ShaderPrimitiveType::VEC3F, 12},
	{BTekEngine::ShaderPrimitiveType::VEC4F, 16},
	{BTekEngine::ShaderPrimitiveType::INT, 4},
	{BTekEngine::ShaderPrimitiveType::VEC2I, 8},
	{BTekEngine::ShaderPrimitiveType::VEC3I, 12},
	{BTekEngine::ShaderPrimitiveType::VEC4I, 16},
	{BTekEngine::ShaderPrimitiveType::MAT2X2F, 16},
	{BTekEngine::ShaderPrimitiveType::MAT3X3F, 36},
	{BTekEngine::ShaderPrimitiveType::MAT4X4F, 64},
};

int BTekEngine::GfxGetShaderPrimitiveSize(ShaderPrimitiveType type) {
	return shader_var_sizes.at(type);
}