#pragma once
#include "VertexBuffer.h"
#include "GraphicsApi.h"
#include "IndexBuffer.h"
#include "Texture2D.h"

namespace BTekEngine {

	class StaticMesh : public GfxApiObject {
	public:
		StaticMesh();

		void SetVertices(VertexBuffer* buffer, MeshAttribDescriptor desc);
		void SetColors(VertexBuffer* buffer, MeshAttribDescriptor desc);
		void SetUVs(VertexBuffer* buffer, MeshAttribDescriptor desc);
		void SetTexture(Texture2D* texture);
		void SetIndices(IndexBuffer* buffer);

		void Render();

		~StaticMesh();
	private:
		VertexBuffer* m_pVertices = 0;
		VertexBuffer* m_pColors = 0;
		VertexBuffer* m_pUVs = 0;

		Texture2D* m_mainTexture = 0;

		int m_gfxApiHandle = -1;
		int m_drawElementCount = -1;
		int m_drawElementStart = 0;
		int m_gfxApiIndexBuffer = -1;
		bool m_usesIndices = false;
		bool m_hasTexture = false;
		
		
	};
}