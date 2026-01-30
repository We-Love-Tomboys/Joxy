#include <joxy/renderer/program.hpp>

Program::Program(Shader &vertShader, Shader &fragShader)
{
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertShader.ID);
    glAttachShader(this->ID, fragShader.ID);
    glLinkProgram(this->ID);
    int success;
    char info[1024];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->ID, 512, NULL, info);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info << std::endl;
    }
}

Program::~Program()
{
    glDeleteProgram(this->ID);
}

void Program::use()
{
    glUseProgram(this->ID);
}

void Program::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
void Program::setFloat(const std::string &name, float value) const
{   
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Program::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Program::setMat4(const std::string &name, glm::mat4 value) const{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}