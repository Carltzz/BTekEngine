#include "Window.h"

WindowSize Window::GetSize() {
	return { m_width, m_height };
}

std::string Window::GetTitle() {
	return std::string(m_title);
}

void Window::SetSize(WindowSize size) {
	SetSize(size.Width, size.Height);
}