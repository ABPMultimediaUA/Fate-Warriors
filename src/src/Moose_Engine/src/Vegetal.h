#ifndef VEGETAL_H
#define VEGETAL_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Objeto_Vegetacion.h"


struct Vegetal : public Objeto_Vegetacion {
    Vegetal(glm::vec3 _i_Position, float rotacion, GLuint imagen) : Objeto_Vegetacion(_i_Position,rotacion, imagen) {}
    void actualizar_visualizacion(glm::mat4& ModelMatrix, glm::mat4 view) override{};
};
#endif 
