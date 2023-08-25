#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "Window.h"

namespace BTekEngine {
	class MSWindow : public Window {
	public:
		MSWindow(const char* title, int width, int height);

		void SetSize(int width, int height) override;
		void SetTitle(const char* newTitle) override;

		WIN_RETURN_STATUS Run() override;
	private:
		HWND m_hWnd = NULL;
	};

	WIN_RETURN_STATUS RegisterWindowClass();
}



#endif