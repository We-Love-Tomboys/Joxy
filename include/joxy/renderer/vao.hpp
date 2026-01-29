#ifndef VAO_HPP
#define VAO_HPP

#include <joxy/include.hpp>
#include "vbo.hpp"

class VAO{
    public:
        VAO();
        ~VAO();
        void bind();
        void unbind();
        void link(VBO &vbo, unsigned int idx, size_t size, size_t stride, size_t offset);
        unsigned int ID;
};

#endif