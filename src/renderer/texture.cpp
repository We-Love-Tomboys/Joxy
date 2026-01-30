#include <joxy/renderer/texture.hpp>

Texture::Texture(const char *filepath, GLenum type, GLenum slot)
{
    unsigned char *texData = stbi_load(filepath, &this->width, &this->height, &this->nrChannels, 0);
    if (texData)
    {
        glGenTextures(1, &this->ID);
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, type, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(texData);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &this->ID);
}

void Texture::texUnit(Program &shaderProgram, const char *uniform, unsigned int id){
    shaderProgram.use();
    shaderProgram.setInt(uniform, id);
}