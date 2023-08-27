cmake_minimum_required (VERSION 3.8)

add_subdirectory(Graphics)
add_subdirectory(Math)
add_subdirectory(Util)

set(ENGINE_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Engine.h
	${GRAPHICS_SOURCES}
	${MATH_SOURCES}
	${UTIL_SOURCES}
	PARENT_SCOPE)