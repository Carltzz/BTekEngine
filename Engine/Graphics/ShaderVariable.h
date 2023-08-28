#pragma once
#include "BufferObject.h"

namespace BTekEngine {

	class ShaderVariable : public GfxApiObject {
	public:
		ShaderVariable(
			int parentId,
			ShaderPrimitiveType type, 
			const std::string& name,
			int size = -1);

		void UpdateData(
			void* data, 
			int dstOffset = 0, 
			int size = -1);

		int GetLocation();

		~ShaderVariable();
	private:
		ShaderPrimitiveType m_primitiveType;
		std::string m_name;
		int m_location;
		int m_shaderId;
	};
}