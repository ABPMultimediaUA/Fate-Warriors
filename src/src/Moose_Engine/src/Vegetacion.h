#ifndef VEGETACION_H
#define VEGETACION_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Vegetal.h"
#include "Cesped.h"


class Shader;


// Types of loaded shaders
enum VegataType {
    Enum_Vegetal = 0,
    Enum_Cesped,
    Vegetal_count
};




class Vegetacion {
public:
    Vegetacion(Shader* _i_shader);
    void draw();
    ~Vegetacion();
 
private:

    void init();
    GLuint load_texture(const char* ruta, VegataType vegetal);
    glm::mat4 update_model_matrix(glm::vec3 position, float grados, float grados_y, glm::vec3 rotation, glm::vec3 escalado);

    std::vector<const GLchar*> faces;
    GLuint cubemapTexture;

    std::vector<Objeto_Vegetacion*> clouds;
    void update(float dt);


    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    Shader* shader;
    glm::mat4 _traslacion;
    glm::mat4 _rotacion;
    glm::mat4 _escalado;
    glm::mat4 ModelMatrix;


    GLuint Imagenes[Vegetal_count];

     GLuint ID;

};

#endif 
