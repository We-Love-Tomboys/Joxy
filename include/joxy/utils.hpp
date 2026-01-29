#ifndef UTILS_HPP
#define UTILS_HPP

#include "include.hpp"

struct Color
{
    float r, g, b, a;
};

Color RGBA255toRGBA1(int r, int g, int b, int a)
{
    return {
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        a / 255.0f};
}

void log_gpu_info()
{
    // Source - https://stackoverflow.com/a
    // Posted by anom1, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-01-28, License - CC BY-SA 4.0
    std::string mystring;
    std::cout << "" << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;

    std::string Vendor(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    std::string Renderer(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    std::string Version(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    std::string ShadingLanguageVersion(reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    mystring = "\n";
    mystring = "OpenGL Vendor: " + Vendor + "\n";
    mystring = "OpenGL Renderer : " + Renderer + "\n";
    mystring = "OpenGL Version: " + Version + "\n";
    mystring = "OpenGL Shading Language Version: " + ShadingLanguageVersion + "\n";
    mystring = "\n";
}

#endif