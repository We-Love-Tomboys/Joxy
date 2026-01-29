#include <joxy/renderer/ebo.hpp>

EBO::EBO(unsigned int *indices, size_t count)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &this->ID);
}

void EBO::bind()
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}