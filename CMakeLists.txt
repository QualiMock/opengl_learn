cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(proj_name Learning)

project(${proj_name})

set(CMAKE_CXX_STANDART 17)

add_executable(${proj_name} 
    src/main.cpp
    src/renderer/ShaderProgram.cpp
    src/renderer/ShaderProgram.h
    src/resources/ResourceManager.cpp
    src/resources/ResourceManager.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLWF_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${proj_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${proj_name} glad)

set_target_properties(${proj_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${proj_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${proj_name}>/res)
