#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <joxy/include.hpp>
#include "program.hpp"

class Texture
{
public:
    Texture(const char *filepath, GLenum type, GLenum slot);
    ~Texture();
    void texUnit(Program &shaderProgram, const char *uniform, unsigned int id);
    unsigned int ID;
    int width;
    int height;
    int nrChannels;
};

#endif