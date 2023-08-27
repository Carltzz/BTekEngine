cmake_minimum_required(VERSION 3.8)

set(UTIL_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Logger.h
	${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.h
	${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLoggerImpl.h
	PARENT_SCOPE
)