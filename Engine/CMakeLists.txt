cmake_minimum_required (VERSION 3.8)

add_subdirectory(Core)

set(ENGINE_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Engine.h
	${CORE_SOURCES}
	PARENT_SCOPE)