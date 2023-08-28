#pragma once
#include "GraphicsApi.h"

namespace BTekEngine {
	class Texture2D : public GfxApiObject {
	public:
		Texture2D(int width, int height);

		void SetPixels(void* data);
		void SetWrappingMode(int mode) { }

		int GetID();

		~Texture2D();
	private:
		int m_width = -1;
		int m_height = -1;
		int m_gfxTextureId = -1;
	};
}