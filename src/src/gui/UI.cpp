#include "UI.h"
#include <stdio.h>
#include <glad/glad.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>


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

    _window = window;
    _ancho_ventana = ancho_ventana;
    _alto_ventana = alto_ventana;

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

GLuint UI::read_image(const char* imagen){

}