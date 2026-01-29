add_library(renderer
    program.cpp
    vbo.cpp
    vao.cpp
    ebo.cpp
    shader.cpp
)

target_include_directories(renderer PUBLIC ${PROJECT_SOURCE_DIR}/include)


target_link_libraries(renderer
    PUBLIC
        glad
        glfw
)