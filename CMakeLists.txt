﻿# CMakeList.txt : CMake project for BTekEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(BTekEngine)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET BTekEngine PROPERTY CXX_STANDARD 20)
# endif()

# TODO: Add tests and install targets if needed.
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/glew-2.2.0" ${CMAKE_PREFIX_PATH})

add_subdirectory(Engine)
add_subdirectory(Snake)

message(${CMAKE_PREFIX_PATH})
find_package(GLEW REQUIRED)

add_library(BTekEngine SHARED ${ENGINE_SOURCES})
target_link_libraries(BTekEngine ${GLEW_LIBRARIES})
target_include_directories(BTekEngine PRIVATE Engine)
target_include_directories(BTekEngine PRIVATE ${GLEW_INCLUDE_DIRS})

add_executable(BTekSnake ${SNAKE_SOURCES})
target_link_libraries(BTekSnake BTekEngine)
target_include_directories(BTekSnake PRIVATE Engine)
