#ifdef _WIN32
#include "OpenGLApiWindows.h"
#include "Engine.h"
#include <Windows.h>
#include <gl/glew.h>

#pragma comment (lib, "opengl32.lib")

using namespace BTekEngine;

const PIXELFORMATDESCRIPTOR defaultPfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0, 0, 0, 0, 0, 0,
	0, 0, 0,
	0, 0, 0, 0,
	24, 8, 0,
	PFD_MAIN_PLANE,
	0, 0, 0,
	0
};

void OpenGLApiWindows::Init() {
	HWND hWnd = reinterpret_cast<HWND>(m_pWindow);
	HDC deviceContext = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd = PIXELFORMATDESCRIPTOR(defaultPfd);
	int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
	SetPixelFormat(deviceContext, pixelFormat, &pfd);

	HGLRC renderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, renderContext);

	GLenum glewInitResult = glewInit();
	if (glewInitResult == GLEW_OK) {
		BTekLogMessage(LogLevel::INFO, "Successfully loaded GLEW");
	}

	LoadCoreShaders();
}

#endif