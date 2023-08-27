#pragma once
#include "Math/Vector.h"

enum class GraphicsApiType {
	OpenGL,
	DirectX,
	// TODO: Vulkan, Metal
};

namespace BTekEngine {
	class GraphicsApi {
	public:
		GraphicsApi(void* window) : m_pWindow(window) { }

		virtual void Init() = 0;
		virtual void PrepareRender() = 0;
		virtual void FinishRender() = 0;

		virtual void DrawRectangle(Vector3<double> Start, Vector3<double> End) = 0;

		virtual void SetViewport(double x, double y, double width, double height) = 0;
		virtual void SetClearColor(Color3<double> clearColour) = 0;
		virtual void SetClearColor(double r, double g, double b) = 0;
		virtual void ClearBuffers() = 0;
	
	protected:
		void* m_pWindow;
	};

	GraphicsApi* CreateGraphicsApi(void* windowBase, GraphicsApiType apiType);
}