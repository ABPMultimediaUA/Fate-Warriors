#ifndef OBJETO_VEGETACION_H
#define OBJETO_VEGETACION_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

 
struct Objeto_Vegetacion {
    glm::vec3 Position;
    float _rotacion;
    float _rotacion_x;
    Objeto_Vegetacion() : Position(0.0f){ }
    Objeto_Vegetacion(glm::vec3 _i_Position, float rotacion) : Position(_i_Position), _rotacion(rotacion), _rotacion_x(0){}
    virtual void actualizar_visualizacion(glm::mat4& ModelMatrix, glm::mat4 view){};

};

#endif 
