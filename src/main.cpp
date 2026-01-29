#include <iostream>
#include <joxy/utils.hpp>
#include <joxy/renderer/shader.hpp>
#include <joxy/renderer/program.hpp>
#include <joxy/renderer/vao.hpp>
#include <joxy/renderer/vbo.hpp>
#include <joxy/renderer/ebo.hpp>
#include <joxy/ui/ui.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char const *argv[])
{
    std::cout << "JOXY 0.0.1" << std::endl;
    GLFWwindow *window;
    Color bg = RGBA255toRGBA1(65, 138, 234, 255);

    {

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
        {

            glDebugMessageCallback(
                [](GLenum source, GLenum type, GLuint id,
                   GLenum severity, GLsizei length,
                   const GLchar *message, const void *userParam)
                {
                    std::cerr << "GL DEBUG: " << message << std::endl;
                },
                nullptr);
        }
    }

    float vertices[] = {
        // positions      // colors          // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0,
        1,
        3,
        1,
        2,
        3,
    };
    float texCoords[] = {
        0.0f, 0.0f, // lower-left corner
        1.0f, 0.0f, // lower-right corner
        0.5f, 1.0f  // top-center corner
    };

    VAO vao = VAO();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.link(vbo, 0, 3, 8, 0);
    vao.link(vbo, 1, 3, 8, 3);
    vao.link(vbo, 2, 2, 8, 6);

    vbo.unbind();

    Shader vertexShader("shaders/default.vert", ShaderType::VertexShader);
    Shader fragmentShader("shaders/default.frag", ShaderType::FragmentShader);
    Program shaderProgram(vertexShader, fragmentShader);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *texData = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
    if (texData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(texData);

    joxy::ui::init(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        joxy::ui::begin_frame();
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, (void *)0);
        joxy::ui::end_frame();
        glfwSwapBuffers(window);
    }
    joxy::ui::shutdown();
    glfwTerminate();
    return 0;
}
