add_library(renderer
    program.cpp
    vbo.cpp
    vao.cpp
    ebo.cpp
    shader.cpp
    texture.cpp
    stb_image.cpp
)

target_include_directories(renderer PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(renderer PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/stb)


target_include_directories(renderer PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty/glm)
target_link_libraries(renderer PUBLIC glm::glm)

target_link_libraries(renderer
    PUBLIC
        glad
        glfw
)