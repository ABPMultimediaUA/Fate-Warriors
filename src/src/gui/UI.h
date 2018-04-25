
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>

class UI{
    public: 
        static UI* ui_instancia(uint16_t ancho_ventana, uint16_t alto_ventana, GLFWwindow* window);
        UI(uint16_t ancho_ventana, uint16_t alto_ventana, GLFWwindow* window);
        ~UI();
        void update();
        void render();

        GLuint read_image(const char* imagen);
        void cargar_res_1920();
    private:
        //static void error_callback(int error, const char* description);
        GLFWwindow* _window;
        static UI* _instancia;
        uint16_t _ancho_ventana;
        uint16_t _alto_ventana;

        uint16_t _boton_ancho;
        uint16_t _boton_alto;
        uint16_t _posicion_menu_std_X;   //posicion para el menu principal
        uint16_t _posicion_menu_std_Y; 
};