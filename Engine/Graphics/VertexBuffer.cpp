#include "VertexBuffer.h"
#include "GraphicsApi.h"
#include "Engine.h"

using namespace BTekEngine;

BTekEngine::VertexBuffer::VertexBuffer(int sizeInBytes, void* data, int elements) :
	BufferObject(sizeInBytes, data, elements) {
	m_loadInitialData(sizeInBytes, data);
}

void BTekEngine::VertexBuffer::m_loadInitialData(int sizeInBytes, void* data) {
	m_gfxApiHandle = m_gfxApi->CreateVertexBuffer(sizeInBytes, data);
}

BTekEngine::VertexBuffer::~VertexBuffer() {
	m_gfxApi->DeleteVertexBuffer(m_gfxApiHandle);
}