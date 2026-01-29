#include <iostream>
#include <joxy/utils.hpp>
#include <joxy/renderer/shader.hpp>
#include <joxy/renderer/program.hpp>
#include <joxy/ui/ui.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char const *argv[])
{
    std::cout << "JOXY 0.0.1" << std::endl;

    GLFWwindow *window;

    if (!glfwInit())
    {
        std::cout << "Failed to Init GLFW\n";
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "[JOXY]", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        std::cout << "Failed to create window\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load OpenGL\n";
        return -1;
    }

    // IMP: LOG GPU VERSION AFTER CREATING AN OPENGL CTX
    log_gpu_info();

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id,
           GLenum severity, GLsizei length,
           const GLchar *message, const void *userParam)
        {
            std::cerr << "GL DEBUG: " << message << std::endl;
        },
        nullptr);

    Color bg = RGBA255toRGBA1(65, 138, 234, 255);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    Shader vertexShader("shaders/default.vert", ShaderType::VertexShader);
    Shader fragmentShader("shaders/default.frag", ShaderType::FragmentShader);

    Program shaderProgram(vertexShader, fragmentShader);

    // This tells gpu how the vertex data is getting sent to the vram, we use it later
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Actual vertex buffer object which we will sent to gpu
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Now we tell how the data is actually represented.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    joxy::ui::init(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        joxy::ui::begin_frame();
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram.ID);
        glBindVertexArray(VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        joxy::ui::end_frame();
        glfwSwapBuffers(window);
    }
    joxy::ui::shutdown();
    glfwTerminate();
    return 0;
}
