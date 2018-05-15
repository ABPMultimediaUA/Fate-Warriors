#ifndef CESPED_H
#define CESPED_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Objeto_Vegetacion.h"
#include "glm/ext.hpp"

#include <iostream>


struct Cesped : public Objeto_Vegetacion {
    Cesped(glm::vec3 _i_Position, float rotacion, GLuint imagen) : Objeto_Vegetacion(_i_Position,rotacion, imagen) {}
    void actualizar_visualizacion(glm::mat4& ModelMatrix, glm::mat4 view) override{
        /*
        ModelMatrix[0][0] = view[0][0]; 
        ModelMatrix[1][0] = view[0][1];
        ModelMatrix[2][0] = view[0][2];

        ModelMatrix[0][1] = view[1][0];
        ModelMatrix[1][1] = view[1][1];
        ModelMatrix[2][1] = view[1][2];

        ModelMatrix[0][2] = view[2][0];
        ModelMatrix[1][2] = view[2][1];
        ModelMatrix[2][2] = view[2][2];

        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.0f), glm::vec3(0,0,1));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(32,4,4));
        **/
    };
};

#endif 
