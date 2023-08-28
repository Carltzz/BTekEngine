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
		int CreateIndexBuffer(int sizeInBytes, void* data) override;
		void DeleteIndexBuffer(int id) override;

		int CreateShader();
		int CreateShaderStage(ShaderType shaderType);
		bool CompileShaderStage(int id, const char* src);
		bool CompileShader(int id, ShaderDescriptor desc);
		void ActivateShader(int id);
		void DeleteShaderStage(int id);
		void DeleteShader(int id);
		
		int AllocateMesh() override;
		void DeallocateMesh(int meshId) override;
		void SetMeshAttribute(int meshId, MeshAttribDescriptor desc) override;
		void DrawMesh(int meshId, int startVertex, int count) override; 
		void DrawIndexedMesh(int meshId, int indexBufferId, int startIndex, int count) override;

		int DefineShaderVariable(
			int shaderId,
			ShaderPrimitiveType type,
			const std::string& name,
			int size) override;

		void UpdateShaderVariable(
			int shaderId,
			ShaderPrimitiveType type,
			int location,
			void* data, 
			int dstOffset, 
			int size) override;

		void DeleteShaderVariable(
			ShaderPrimitiveType type,
			int id) override;

		void LoadCoreShaders();
		void CleanUp();
	};
}