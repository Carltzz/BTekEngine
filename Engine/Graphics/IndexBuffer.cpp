#include "IndexBuffer.h"

using namespace BTekEngine;

BTekEngine::IndexBuffer::IndexBuffer(int sizeInBytes, void* data, int elements) :
	BufferObject(sizeInBytes, data, elements) {
	m_loadInitialData(sizeInBytes, data);
}


void BTekEngine::IndexBuffer::m_loadInitialData(int sizeInBytes, void* data) {
	m_gfxApiHandle = m_gfxApi->CreateIndexBuffer(sizeInBytes, data);
}

BTekEngine::IndexBuffer::~IndexBuffer() {
	m_gfxApi->DeleteIndexBuffer(m_gfxApiHandle);
}