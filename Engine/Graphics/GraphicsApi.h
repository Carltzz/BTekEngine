#pragma once
#include "Engine.h"
#include "Math/Vector.h"

enum class GraphicsApiType {
	OpenGL,
	DirectX,
	// TODO: Vulkan, Metal
};

namespace BTekEngine {
	enum class MeshAttribute {
		POSITION,
		COLOUR,
		UV,
		NORMAL
	};

	struct MeshAttribDescriptor {
		int BufferId;
		MeshAttribute Attribute;
		int Components;
		int Stride;
		int Size;
	};

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
		
		virtual int AllocateMesh() = 0;
		virtual void DeallocateMesh(int meshId) = 0;
		virtual void SetMeshAttribute(int meshId, MeshAttribDescriptor desc) = 0;
		virtual void DrawMesh(int meshId, int startVertex, int count) = 0;
		virtual void DrawIndexedMesh(int meshId, int indexBufferId, int startIndex, int count) = 0;

		virtual int CreateVertexBuffer(int sizeInBytes, void* data) = 0;
		virtual void DeleteVertexBuffer(int id) = 0;
		virtual int CreateIndexBuffer(int sizeInBytes, void* data) = 0;
		virtual void DeleteIndexBuffer(int id) = 0;

	protected:
		void* m_pWindow;
	};

	class GfxApiObject {
	public:
		GfxApiObject() {
			m_gfxApi = static_cast<GraphicsApi*>(GetGraphicsApi());
		}
	protected:
		GraphicsApi* m_gfxApi;
	};

	GraphicsApi* CreateGraphicsApi(void* windowBase, GraphicsApiType apiType);
}