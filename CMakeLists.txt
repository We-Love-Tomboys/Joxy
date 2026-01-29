cmake_minimum_required(VERSION 3.15)

project(joxy VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/glfw)

# GLAD
add_library(glad thirdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC thirdparty/glad/include)

add_subdirectory(thirdparty/imgui)


# Your code
add_subdirectory(src)

# Executable
add_executable(joxy src/main.cpp)

target_link_libraries(joxy
    PRIVATE
        glad
        OpenGL::GL
        renderer
        imgui
        ui
    PUBLIC
        glfw
)

target_include_directories(joxy PUBLIC include)


# Copy shaders next to exe
add_custom_command(
    TARGET joxy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:joxy>/shaders
)
