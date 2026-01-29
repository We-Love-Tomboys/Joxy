#include <joxy/renderer/program.hpp>

Program::Program(Shader &vertShader, Shader &fragShader)
{
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertShader.ID);
    glAttachShader(this->ID, fragShader.ID);
    glLinkProgram(this->ID);
}

Program::~Program()
{
    glDeleteProgram(this->ID);
}