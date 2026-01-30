#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <joxy/include.hpp>
#include "shader.hpp"

class Program
{
public:
    Program(Shader &vertShader, Shader &fragShader);
    ~Program();
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;

    unsigned int ID;
};

#endif