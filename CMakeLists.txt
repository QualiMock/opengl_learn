cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(proj_name Learning)

project(${proj_name})

set(CMAKE_CXX_STANDART 17)

add_executable(${proj_name} 
    src/main.cpp
    src/renderer/shader_program.cpp
    src/renderer/shader_program.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLWF_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${proj_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${proj_name} glad)
