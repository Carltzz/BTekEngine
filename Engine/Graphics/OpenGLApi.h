#pragma once
#include "GraphicsAPI.h"

namespace BTekEngine {
	class OpenGLApi : public GraphicsApi {
	public:
		OpenGLApi(void* window) : GraphicsApi(window) { }

		void DrawRectangle(Vector3<double> Start, Vector3<double> End);
		void SetViewport(double x, double y, double width, double height);
		void SetClearColor(double r, double g, double b);
		void SetClearColor(Color3<double> colour);
		void ClearBuffers();
		void PrepareRender();
		void FinishRender();
	};
}