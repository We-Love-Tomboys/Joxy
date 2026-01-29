#ifndef VBO_HPP
#define VBO_HPP

#include <joxy/include.hpp>

class VBO{
    public:
        VBO(float* vertices, size_t count);
        ~VBO();
        void bind();
        void unbind();
        unsigned int ID;
};

#endif