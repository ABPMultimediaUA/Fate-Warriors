#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>

class UI{
    public: 
        UI();
        ~UI();
    private:
        uint16_t _ancho_ventana;
        uint16_t _alto_ventana;
};