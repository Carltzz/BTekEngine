#pragma once
#include "BufferObject.h"
#include "GraphicsApi.h"

namespace BTekEngine {
	class VertexBuffer : public BufferObject {
	public:
		VertexBuffer(int sizeInbytes, void* data, int elements);
		~VertexBuffer();

	protected:
		void m_loadInitialData(int sizeInBytes, void* data) override;
	};
}