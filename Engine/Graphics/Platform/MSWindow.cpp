#ifdef _WIN32
#include "MSWindow.h"
#include "Graphics/OpenGLApi.h"

const LPCSTR BTEK_CLASS_NAME = "BTekWindow";

using namespace BTekEngine;

struct WindowState {
	Window* window;
};

LRESULT CALLBACK BTekWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	WindowState* pState;

	if (uMsg == WM_CREATE) {
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<WindowState*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else {
		LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
		pState = reinterpret_cast<WindowState*>(ptr);
	}
	
	switch (uMsg) {
		case WM_CREATE: {
			pState->window->InitGraphicsApi(hWnd);
			break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_CLOSE: {
			DestroyWindow(hWnd);
			break;
    	}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	return 0;
};

HWND BTekCreateWindow(Window* window) {
	WindowSize size = window->GetSize();
	WindowState* pState = new WindowState{ window };

	return CreateWindowEx(
		NULL,
		BTEK_CLASS_NAME,
		window->GetTitle().c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		size.Width,
		size.Height,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		pState
	);
}

WIN_RETURN_STATUS BTekEngine::RegisterWindowClass() {
	WNDCLASS wc = { };
	wc.lpfnWndProc = BTekWindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = BTEK_CLASS_NAME;
	RegisterClass(&wc);
	return WIN_RUN_OK;
}

BTekEngine::MSWindow::MSWindow(const char* title, int width, int height) {
	m_title = title;
	m_width = width;
	m_height = height;
}

WIN_RETURN_STATUS BTekEngine::MSWindow::Run(GraphicsApiType api) {
	m_gfxApiType = api;
	BTekCreateWindow(this);

	HDC deviceContext = GetDC(m_hWnd);

	if (!m_hWnd) {
		return WIN_RUN_ERROR;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	Vector3<double> start = { 0, 0, 0 }, end = { 50, 50, 0 };

	MSG msg = { };
	bool quit = false;
	while (true) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				quit = true;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (quit) break;
		
		m_gfxApi->ClearBuffers();
		m_gfxApi->PrepareRender();
		m_gfxApi->DrawRectangle(start, end);
		m_gfxApi->FinishRender();
		SwapBuffers(deviceContext);
	}

	return WIN_RUN_OK;
}

void BTekEngine::MSWindow::SetSize(int width, int height) {
	if (m_hWnd) {
		MoveWindow(m_hWnd, 0, 0, width, height, TRUE);
	}
}

void BTekEngine::MSWindow::SetTitle(const char* newTitle) {
	if (m_hWnd) {
		SetWindowText(m_hWnd, newTitle);
	}
}

HWND BTekEngine::MSWindow::GetHWnd() {
	return m_hWnd;
}

void BTekEngine::MSWindow::InitGraphicsApi(void* hWnd) {
	m_hWnd = (HWND)hWnd;
	m_gfxApi = BTekEngine::CreateGraphicsApi(this, m_gfxApiType);
	m_gfxApi->Init();
	m_gfxApi->SetClearColor(0.0, 1.0, 0.0);
	m_gfxApi->SetViewport(0, 0, m_width, m_height);
}

#endif