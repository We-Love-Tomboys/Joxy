#ifndef JOXY_UI_HPP
#define JOXY_UI_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


namespace joxy::ui
{
    void init(GLFWwindow* window);
    void begin_frame();
    void end_frame();
    void shutdown();
} // namespace joxy::ui


#endif