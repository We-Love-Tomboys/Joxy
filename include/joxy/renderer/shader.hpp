#ifndef SHADER_HPP
#define SHADER_HPP

#include <joxy/include.hpp>
#include <fstream>
#include <sstream>

enum class ShaderType
{
    VertexShader,
    FragmentShader
};

class Shader
{
public:
    Shader(const char *filepath, ShaderType type);
    ~Shader();

    ShaderType type;
    unsigned int ID;
};

#endif