#include "OpenGLApi.h"

#ifdef _WIN32
#include <Windows.h>
#include <gl/GL.h>
#else
#endif

void BTekEngine::OpenGLApi::DrawRectangle(Vector3<double> Start, Vector3<double> End) {
	float sx = (float)Start.X;
	float sy = (float)Start.Y;
	float ex = (float)End.X;
	float ey = (float)End.Y;
	
	glBegin(GL_QUADS);
	glVertex3f(sx, sy, 0);
	glVertex3f(sx, ey, 0);
	glVertex3f(ex, ey, 0);
	glVertex3f(ex, sy, 0);
	glEnd();
}

void BTekEngine::OpenGLApi::PrepareRender() {
	ClearBuffers();
}

void BTekEngine::OpenGLApi::SetViewport(double x, double y, double width, double height) {
	glViewport(x, y, width, height);
}

void BTekEngine::OpenGLApi::SetClearColor(Color3<double> colour) {
	SetClearColor(colour.R, colour.G, colour.B);
}

void BTekEngine::OpenGLApi::SetClearColor(double r, double g, double b) {
	glClearColor((float)r, (float)g, (float)b, 1.0f);
}

void BTekEngine::OpenGLApi::ClearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BTekEngine::OpenGLApi::FinishRender() {
	
}