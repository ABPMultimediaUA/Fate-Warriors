#ifndef NUBES_H
#define NUBES_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;
 
 struct Nube {
    glm::vec3 Position;
    Nube() : Position(0.0f){ }
    Nube(glm::vec3 _i_Position) : Position(_i_Position){}
};


class Nubes {
public:
    Nubes(Shader* _i_shader);
    void draw();
    ~Nubes();
 
private:

    void init();
    GLuint load_texture();
    void update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado);

    std::vector<const GLchar*> faces;
    GLuint cubemapTexture;

    std::vector<Nube> clouds;

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
