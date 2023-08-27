#pragma once
#include <string>

namespace BTekEngine {
	enum class LogLevel {
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		CRITICAL,
		FATAL
	};

	class Logger {
	public:
		virtual void Log(LogLevel level, const std::string& message) = 0;
	};
}