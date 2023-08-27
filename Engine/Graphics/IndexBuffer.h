#pragma once
#include "VertexBuffer.h"

namespace BTekEngine {
	class IndexBuffer : public BufferObject {
	public:
		IndexBuffer(int sizeInBytes, void* data, int elements);
		~IndexBuffer();
	protected:
		void m_loadInitialData(int sizeInBytes, void* data) override;
	};
}