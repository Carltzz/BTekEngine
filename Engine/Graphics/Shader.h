#pragma once
#include "GraphicsApi.h"

namespace BTekEngine {
	class Shader : public GfxApiObject {
	public:
		Shader(const std::string& name);

		bool SetVertexStage(const char* src);
		bool SetHullStage(const char* src);
		bool SetDomainStage(const char* src);
		bool SetGeometryStage(const char* src);
		bool SetPixelStage(const char* src);
		bool SetComputeStage(const char* src);

		bool Compile();
		void Activate();

		~Shader();

	private:
		bool m_hasCompiled = false;
		int m_gfxShaderId = -1;
		std::string m_name = "btek_shader";

		int m_gfxVertexShader = -1;
		int m_gfxHullShader = -1;
		int m_gfxDomainShader = -1;
		int m_gfxGeometryShader = -1;
		int m_gfxPixelShader = -1;
		int m_gfxComputeShader = -1;

		void m_deleteShaderCache();
	};
}