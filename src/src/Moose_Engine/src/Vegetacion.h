#ifndef VEGETACION_H
#define VEGETACION_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;
 
 struct Vegetal {
    glm::vec3 Position;
    float _rotacion;
    Vegetal() : Position(0.0f){ }
    Vegetal(glm::vec3 _i_Position, float rotacion) : Position(_i_Position), _rotacion(rotacion){}
};


class Vegetacion {
public:
    Vegetacion(Shader* _i_shader);
    void draw();
    ~Vegetacion();
 
private:

    void init();
    GLuint load_texture();
    void update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado);

    std::vector<const GLchar*> faces;
    GLuint cubemapTexture;

    std::vector<Vegetal> clouds;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    Shader* shader;
    glm::mat4 _traslacion;
    glm::mat4 _rotacion;
    glm::mat4 _escalado;
    glm::mat4 ModelMatrix;

     GLuint ID;

};

#endif 
