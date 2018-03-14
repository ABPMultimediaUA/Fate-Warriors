
#include <string>
#include <sstream>
#include <fstream>

//OPEN GL 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Interfaz/Motor.h"

void interfazTest(){
    Motor* interfaz_motor = Motor::Motor_GetInstance();
    
    const char cstr[] =  "src/Moose_Engine/Carne.obj";
    const char cstr2[] = "src/Moose_Engine/npc2.obj";
    
    iNodoCamara* camara = interfaz_motor->crearCamara(true);
    //camara->mover(2, 0, 0);    
    iNodoLuz* luz = interfaz_motor->crearLuz(true, 1.0f);

    iNodoModelado* modelado1 = interfaz_motor->crearModelado(cstr, 3, 0, -10);
    iNodoModelado* modelado2 = interfaz_motor->crearModelado(cstr2, 0, 0, -10);

    
    modelado1->mover(-3, 0, -10);
    modelado1->escalar(2,1,1);
    modelado2->escalar(1,2,1);
    camara->mover(-2,0,5);



    while(interfaz_motor->ventana_abierta()){
        interfaz_motor->render();
    }

}

int main(){
    //dibujarOpenGL();
    //recorrerArbol();
    interfazTest();
    return 0;
}