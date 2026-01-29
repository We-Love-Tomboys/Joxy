#include <joxy/renderer/vao.hpp>

VAO::VAO()
{
    glGenVertexArrays(1, &this->ID);
    glBindVertexArray(this->ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &this->ID);
}

void VAO::bind()
{

    glBindVertexArray(this->ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::link(VBO &vbo, unsigned int idx, size_t size, size_t stride, size_t offset)
{
    vbo.bind();
    glVertexAttribPointer(idx, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
    glEnableVertexAttribArray(idx);
    vbo.unbind();
}