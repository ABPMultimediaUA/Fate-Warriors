#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>

class UI{
    public: 
        UI(uint16_t ancho_ventana, uint16_t alto_ventana);
        ~UI();
        void update();
        void render();

    private:
        //static void error_callback(int error, const char* description);

        uint16_t _ancho_ventana;
        uint16_t _alto_ventana;
        bool _show_demo_window;
        ImVec4 _clear_color;
        GLFWwindow* _window;
};