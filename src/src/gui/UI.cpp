#include "UI.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include "SOIL.h"

UI* UI::_instancia = 0;

UI* UI::ui_instancia(uint16_t ancho_ventana, uint16_t alto_ventana, GLFWwindow* window){
	if(_instancia == 0)
		_instancia= new UI(ancho_ventana, alto_ventana, window);
	return _instancia;
}
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}
/*Funciones para guardar los datos
 * */
struct Tresolution2func{//declaracion de los parametros
	int _n_res;
	void (UI::*pmet)();
};

Tresolution2func UI_mapping[] = {//definicion de los parametros
		{1920, &UI::cargar_res_1920}
       /* {1600, &UI::cargar_res_1600},
        {1366, &UI::cargar_res_1366},
        {1280, &UI::cargar_res_1280},
        {1024, &UI::cargar_res_1024},
        {800, &UI::cargar_res_800},
        {640, &UI::cargar_res_640},
		{0, &UI::cargar_res_default}*/
};
UI::UI(uint16_t ancho_ventana, uint16_t alto_ventana, GLFWwindow* window){
    _cierratePuto = false;
    _window = window;
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
    //std::cout<<"algo nbo va bien"<<std::endl;
    }
    _ancho_ventana = ancho_ventana;
    _alto_ventana = alto_ventana;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //_window = glfwCreateWindow(ancho_ventana, alto_ventana, "GUI TEST", NULL, NULL);
    //glfwMakeContextCurrent(_window);
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    //glfwSwapInterval(1); // Enable vsync
    

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);
    // Setup style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    _show_demo_window = true;
    _clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    
    //ImGuiIO& io = ImGui::GetIO();
    //ImFont* pFont = io.Fonts->AddFontFromFileTTF("Goalthink-Regular.ttf", 30.0f);
    //io.FontDefault = pFont;
    //unsigned char* pixels;
    //int width, height;
    //io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);


    Tresolution2func* _next=UI_mapping;
	//std::cout<<_iteracion<<std::endl;
	while (_next->_n_res){
		if(ancho_ventana==_next->_n_res){
			(this->*_next->pmet)();
            break;
		}
		++_next;
	}
    if (! _next->_n_res){
        (this->*_next->pmet)();
    }

    //cargar_res_1920();
}

UI::~UI(){
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
}

void UI::cargar_res_1920(){
    _boton_ancho=300;
    _boton_alto=100;
    _posicion_menu_std_X = (_ancho_ventana/2)-(_boton_ancho/2);
    _posicion_menu_std_Y = (_alto_ventana/2)-(_boton_alto*3/2)-(30*3/2);
}

void UI::update(){
   
}

void UI::render(){

}

bool UI::get_cerrar(){
    return _cierratePuto;
}

GLuint UI::read_image(const char* imagen){
    GLuint textureID;

    glGenTextures(1, &textureID);
    
    int width, height;
    unsigned char* image;
 
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    image = SOIL_load_image(imagen, &width, &height, 0, SOIL_LOAD_RGB);
        
    if (!image) {
        std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
    }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    return textureID;
}