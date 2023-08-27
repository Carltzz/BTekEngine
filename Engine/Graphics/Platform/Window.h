#pragma once
#include <string>
#include "Graphics/GraphicsApi.h"

#define WIN_RUN_ERROR -1
#define WIN_RUN_OK 0

namespace BTekEngine {
	typedef int WIN_RETURN_STATUS;

	struct WindowSize {
		int Width;
		int Height;
	};

	// A structure that defines the screen's viewport container.
	class Window {
	public:

		WindowSize GetSize();
		std::string GetTitle();
		
		virtual void InitGraphicsApi(void* nativeHandle) = 0;
		GraphicsApi* GetGraphicsApi();

		virtual void SetTitle(const char* newTitle) = 0;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetSize(WindowSize size);

		virtual WIN_RETURN_STATUS Run() = 0;
		
	protected:
		// The title of the window
		const char* m_title = 0;

		// The viewport width of the window
		int m_width = 0;

		//The viewport height of the window
		int m_height = 0;

		GraphicsApi* m_gfxApi = 0;
		GraphicsApiType m_gfxApiType = GraphicsApiType::OpenGL;
	};
}

