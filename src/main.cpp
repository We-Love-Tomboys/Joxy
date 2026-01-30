#include <iostream>
#include <joxy/utils.hpp>
#include <joxy/renderer/shader.hpp>
#include <joxy/renderer/program.hpp>
#include <joxy/renderer/vao.hpp>
#include <joxy/renderer/vbo.hpp>
#include <joxy/renderer/ebo.hpp>
#include <joxy/renderer/texture.hpp>
#include <joxy/ui/ui.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 600

void processInput(GLFWwindow *window);

glm::vec3 cameraPosition(0.f, 0.f, 3.f);
glm::vec3 cameraFront(0.f, 0.f, -1.f);
glm::vec3 cameraUp(0.f, 1.f, 0.f);

float dt = 0.f;
float lastFrame = 0.f;

int main(int argc, char const *argv[])
{
    stbi_set_flip_vertically_on_load(true);
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

    // float vertices[] = {
    //     // positions       // colors         // texture coords
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    // };
    // unsigned int indices[] = {
    //     0,
    //     1,
    //     3,
    //     1,
    //     2,
    //     3,
    // };
    // float texCoords[] = {
    //     0.0f, 0.0f, // lower-left corner
    //     1.0f, 0.0f, // lower-right corner
    //     0.5f, 1.0f  // top-center corner
    // };
    // EBO ebo(indices, sizeof(indices));

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    VAO vao = VAO();
    VBO vbo(vertices, sizeof(vertices));

    // vao.link(vbo, 1, 3, 8, 3); // Color
    // vao.link(vbo, 2, 2, 8, 6); // Tex Coord [OLD]

    vao.link(vbo, 0, 3, 5, 0); // Vertex Position
    vao.link(vbo, 2, 2, 5, 3); // Tex Coord [OLD]

    vbo.unbind();

    Shader vertexShader("shaders/default.vert", ShaderType::VertexShader);
    Shader fragmentShader("shaders/default.frag", ShaderType::FragmentShader);
    Program shaderProgram(vertexShader, fragmentShader);

    Texture container("assets/container.jpg", GL_RGB, GL_TEXTURE0);
    Texture face("assets/awesomeface.png", GL_RGBA, GL_TEXTURE1);
    container.texUnit(shaderProgram, "tex1", 0);
    face.texUnit(shaderProgram, "tex2", 1);

    joxy::ui::init(window);

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 position(0.f);
    glm::vec3 rotation(0.f);
    glm::vec3 scale(1.f);

    float fov = 60.f;

    glm::vec3 camera(0.f, 0.f, 3.f);
    glm::vec3 target(0.f, 0.f, 0.f);
    glm::vec3 camDirection = glm::normalize(camera - target);
    glm::vec3 up(0.f, 1.f, 0.f);
    glm::vec3 camRight = glm::normalize(glm::cross(up, camDirection));
    glm::vec3 cameraUp = glm::cross(camDirection, camRight);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glfwPollEvents();
        joxy::ui::begin_frame();
        ImGui::SliderFloat("FOV", &fov, 35.f, 100.f);
        projection = glm::perspective(glm::radians(fov), ((float)WIDTH / (float)HEIGHT), 1.f, 100.f);
        ImGui::DragFloat3("Position", &position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &rotation.x, 0.1f, 0, 360);

        model = glm::mat4(1.f);
        model = glm::rotate(model, glm::radians(rotation.x), {1, 0, 0});
        model = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});
        model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
        model = glm::translate(model, position);

        view = glm::lookAt(
            cameraPosition,
            cameraPosition + cameraFront,
            cameraUp);

        glClearColor(bg.r, bg.g, bg.b, bg.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();

        // Send to the uniform
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        vao.bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, (void *)0);

        joxy::ui::end_frame();
        glfwSwapBuffers(window);
    }
    joxy::ui::shutdown();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{

    float currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;
    const float cameraSpeed = 2.5f * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}