#pragma once
#include "GraphicsAPI.h"

namespace BTekEngine {
	class OpenGLApi : public GraphicsApi {
	public:
		OpenGLApi(void* window) : GraphicsApi(window) { }

		void DrawRectangle(Vector3<double> Start, Vector3<double> End) override;
		void SetViewport(double x, double y, double width, double height) override;
		void SetClearColor(double r, double g, double b) override;
		void SetClearColor(Color3<double> colour) override;

		void ClearBuffers() override;
		void PrepareRender() override;
		void FinishRender() override;

		int CreateVertexBuffer(int sizeInBytes, void* data) override;
		void DeleteVertexBuffer(int id) override;
		virtual int CreateIndexBuffer(int sizeInBytes, void* data) override;
		virtual void DeleteIndexBuffer(int id) override;
		
		int AllocateMesh() override;
		void DeallocateMesh(int meshId) override;
		void SetMeshAttribute(int meshId, MeshAttribDescriptor desc) override;
		void DrawMesh(int meshId, int startVertex, int count) override; 
		void DrawIndexedMesh(int meshId, int indexBufferId, int startIndex, int count) override;


		void LoadCoreShaders();
		void CleanUp();
	};
}