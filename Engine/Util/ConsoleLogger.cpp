#include "ConsoleLogger.h"
#include <cstdarg>
#include <iostream>
#include <map>

using namespace BTekEngine;

const std::map<LogLevel, std::string> log_prefixes = {
	{LogLevel::DEBUG, "[DEBUG] "},
	{LogLevel::INFO, "[INFO] "},
	{LogLevel::WARNING, "[WARNING] "},
	{LogLevel::ERROR, "[ERROR] "},
	{LogLevel::CRITICAL, "[CRITICAL] "},
	{LogLevel::FATAL, "[FATAL] "}
};

void BTekEngine::ConsoleLogger::Log(
	LogLevel level,
	const std::string& message
) {
	std::cout << log_prefixes.at(level) << message << std::endl;
}