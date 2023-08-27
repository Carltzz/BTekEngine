#include "Mesh.h"
#include "Graphics/GraphicsApi.h"

using namespace BTekEngine;

BTekEngine::StaticMesh::StaticMesh() :
	GfxApiObject() {
	m_gfxApiHandle = m_gfxApi->AllocateMesh();
}

void BTekEngine::StaticMesh::SetVertices(VertexBuffer* buffer, MeshAttribDescriptor desc) {
	m_gfxApi->SetMeshAttribute(m_gfxApiHandle, desc);
	m_drawElementCount = buffer->GetElementCount();
}

void BTekEngine::StaticMesh::SetIndices(IndexBuffer* indexBuffer) {
	m_gfxApiIndexBuffer = indexBuffer->GetID();
	m_drawElementCount = indexBuffer->GetElementCount();
	m_usesIndices = true;
}

void BTekEngine::StaticMesh::Render() {
	if (m_usesIndices) {
		m_gfxApi->DrawIndexedMesh(
			m_gfxApiHandle, 
			m_gfxApiIndexBuffer, 
			m_drawElementStart, 
			m_drawElementCount);
	} else {
		m_gfxApi->DrawMesh(
			m_gfxApiHandle,
			m_drawElementStart,
			m_drawElementCount);

	}
}

BTekEngine::StaticMesh::~StaticMesh() {
	m_gfxApi->DeallocateMesh(m_gfxApiHandle);
}