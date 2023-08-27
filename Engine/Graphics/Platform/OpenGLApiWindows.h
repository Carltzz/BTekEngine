#pragma once
#include "Graphics/OpenGLApi.h"

namespace BTekEngine {
	class OpenGLApiWindows : public OpenGLApi {
	public:
		OpenGLApiWindows(void* window) : OpenGLApi(window) { }

		void Init() override;
	};
}