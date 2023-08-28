#include "Shader.h"

using namespace BTekEngine;

BTekEngine::Shader::Shader(const std::string& name) :
	 GfxApiObject() {
	m_gfxShaderId = m_gfxApi->CreateShader();
	m_name = name;
}

bool BTekEngine::Shader::SetVertexStage(const char* src) {
	m_gfxVertexShader = m_gfxApi->CreateShaderStage(ShaderType::Vertex);
	return m_gfxApi->CompileShaderStage(m_gfxVertexShader, src);
}

bool BTekEngine::Shader::SetHullStage(const char* src) {
	m_gfxHullShader = m_gfxApi->CreateShaderStage(ShaderType::Hull);
	return m_gfxApi->CompileShaderStage(m_gfxHullShader, src);
}

bool BTekEngine::Shader::SetDomainStage(const char* src) {
	m_gfxDomainShader = m_gfxApi->CreateShaderStage(ShaderType::Domain);
	return m_gfxApi->CompileShaderStage(m_gfxDomainShader, src);
}

bool BTekEngine::Shader::SetGeometryStage(const char* src) {
	m_gfxGeometryShader = m_gfxApi->CreateShaderStage(ShaderType::Geometry);
	return m_gfxApi->CompileShaderStage(m_gfxGeometryShader, src);
}

bool BTekEngine::Shader::SetPixelStage(const char* src) {
	m_gfxPixelShader = m_gfxApi->CreateShaderStage(ShaderType::Pixel);
	return m_gfxApi->CompileShaderStage(m_gfxPixelShader, src);
}

bool BTekEngine::Shader::SetComputeStage(const char* src) {
	m_gfxComputeShader = m_gfxApi->CreateShaderStage(ShaderType::Compute);
	return m_gfxApi->CompileShaderStage(m_gfxComputeShader, src);
}

int BTekEngine::Shader::AddShaderVariable(ShaderPrimitiveType type, const std::string& name, int size) {
	ShaderVariable* variable = new ShaderVariable(
		m_gfxShaderId,
		type,
		name,
		size
	);
	m_shaderVariables.insert({ variable->GetLocation(), variable });
	return variable->GetLocation();
}

void BTekEngine::Shader::UpdateShaderVariable(int id, void* data, int start, int size) {
	ShaderVariable* var = m_shaderVariables.at(id);
	var->UpdateData(data, start, size);
}

void BTekEngine::Shader::DeleteShaderVariable(int id) {
	ShaderVariable* var = m_shaderVariables.at(id);
	m_shaderVariables.erase(id);
	delete var;
}

bool BTekEngine::Shader::Compile() {
	m_hasCompiled = m_gfxApi->CompileShader(m_gfxShaderId,
		{
			m_gfxVertexShader,
			m_gfxHullShader,
			m_gfxDomainShader,
			m_gfxGeometryShader,
			m_gfxPixelShader,
			m_gfxComputeShader
		});
	m_deleteShaderCache();
	return m_hasCompiled;
}

void BTekEngine::Shader::Activate() {
	if (!m_hasCompiled) return;
	m_gfxApi->ActivateShader(m_gfxShaderId);
}

void deleteShader(GraphicsApi* api ,int& id) {
	if (id != -1) { api->DeleteShaderStage(id); id = -1; }
}

void BTekEngine::Shader::m_deleteShaderCache() {
	deleteShader(m_gfxApi, m_gfxVertexShader);
	deleteShader(m_gfxApi, m_gfxHullShader);
	deleteShader(m_gfxApi, m_gfxDomainShader);
	deleteShader(m_gfxApi, m_gfxGeometryShader);
	deleteShader(m_gfxApi, m_gfxPixelShader);
	deleteShader(m_gfxApi, m_gfxComputeShader);
}

BTekEngine::Shader::~Shader() {
	m_gfxApi->DeleteShader(m_gfxShaderId);
}