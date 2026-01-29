#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <joxy/include.hpp>
#include "shader.hpp"

class Program
{
public:
    Program(Shader &vertShader, Shader &fragShader);
    ~Program();

    unsigned int ID;
};

#endif