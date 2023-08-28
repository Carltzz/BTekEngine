#include "ShaderVariable.h"
#include <map>

BTekEngine::ShaderVariable::ShaderVariable(
	int parentId,
	ShaderPrimitiveType type, 
	const std::string& name,
	int size) {
	m_name = name;
	m_shaderId = parentId;
	m_primitiveType = type;
	m_location = m_gfxApi->DefineShaderVariable(parentId, type, m_name, size);
}

void BTekEngine::ShaderVariable::UpdateData(void* data, int dstOffset, int size) {
	m_gfxApi->UpdateShaderVariable(
		m_shaderId,
		m_primitiveType,
		m_location,
		data,
		dstOffset,
		size);
}

int BTekEngine::ShaderVariable::GetLocation() {
	return m_location;
}

BTekEngine::ShaderVariable::~ShaderVariable() {
	m_gfxApi->DeleteShaderVariable(m_primitiveType, m_location);
}