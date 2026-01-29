#ifndef EBO_HPP
#define EBO_HPP

#include <joxy/include.hpp>

class EBO{
    public:
        EBO(unsigned int* indices, size_t count);
        ~EBO();
        void bind();
        void unbind();
        unsigned int ID;
};

#endif