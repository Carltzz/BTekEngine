#pragma once
#include "Logger.h"

namespace BTekEngine {
	class ConsoleLogger : public Logger {
	public:
		void Log(LogLevel level, const std::string& message);
		
		template<typename... Args>
		void Log(LogLevel level, const std::string& message, Args...);
	};
}

#include "ConsoleLoggerImpl.h"