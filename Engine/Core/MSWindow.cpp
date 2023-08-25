#ifdef _WIN32
#include "MSWindow.h"

const LPCSTR BTEK_CLASS_NAME = "BTekWindow";

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
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_CLOSE: {
			DestroyWindow(hWnd);
			return 0;
    	}
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
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

WIN_RETURN_STATUS BTekEngine::MSWindow::Run() {
	m_hWnd = BTekCreateWindow(this);

	if (!m_hWnd) {
		return WIN_RUN_ERROR;
	}

	ShowWindow(m_hWnd, SW_SHOW);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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

#endif