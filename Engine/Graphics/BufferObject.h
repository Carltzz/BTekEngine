#pragma once
#include "GraphicsApi.h"

namespace BTekEngine {
	class BufferObject : public GfxApiObject {
	public:
		BufferObject(int sizeInBytes, void* data, int elements) :
			GfxApiObject() {
			m_elementCount = elements;
		}

		int GetID() {
			return m_gfxApiHandle;
		}

		int GetElementCount() {
			return m_elementCount;
		}

	protected:
		virtual void m_loadInitialData(int sizeInBytes, void* data) = 0;
		int m_gfxApiHandle = -1;
		int m_elementCount = -1;
	};
}