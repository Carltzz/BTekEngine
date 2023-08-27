#pragma once
#include <iostream>
#include <sstream>
#include "ConsoleLogger.h"

template<typename... Args>
void BTekEngine::ConsoleLogger::Log(
	LogLevel level,
	const std::string& message,
	Args... args
) {
	std::cout << message << " ";
	(void)std::initializer_list<int>{((std::cout << args << " "), 0)...};
	std::cout << std::endl;
}