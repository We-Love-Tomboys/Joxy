#include <joxy/renderer/vbo.hpp>

VBO::VBO(float* vertices, size_t count)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, count *  sizeof(float), vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &this->ID);
}

void VBO::bind()
{

    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}