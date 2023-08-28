#include "Texture2D.h"

BTekEngine::Texture2D::Texture2D(int width, int height) {
	m_width = width;
	m_height = height;
	m_gfxTextureId = m_gfxApi->CreateTexture2D(width, height);
}

void BTekEngine::Texture2D::SetPixels(void* data) {
	m_gfxApi->SetTexture2DPixels(m_gfxTextureId, 0, 0, m_width, m_height, data);
}

int BTekEngine::Texture2D::GetID() {
	return m_gfxTextureId;
}

BTekEngine::Texture2D::~Texture2D() {
	m_gfxApi->DeleteTexture2D(m_gfxTextureId);
}