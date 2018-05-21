#ifndef IMAGE_MAP_H
#define IMAGE_MAP_H
#include <vector>

#include <glm/glm.hpp>

#include "src/Moose_Engine/src/Shader.h"

class Shader;


class Image_Map{
public:

    /*Recibe por parametro el shader, la ruta de la imagen (ruta), la posicion (x,y) y la esccala (width, height)*/
    Image_Map(Shader* shader,GLuint ruta, float x, float y, float width, float height); 
    ~Image_Map();

    /*Dibuja la textura*/
    void Draw();

    /* Pone la textura en una posicion dada (la rotacion no) ya que no todos los objetos deben rotar*/
    void setTextureposition(float x, float y, float rotacion);

    /* Almacena en el shader la rotacion que tiene */
    void update_rotacion();

private:

    // Render state
    Shader* shader;

    //Datos sobre el posicionamiento
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // Initializes buffer and vertex attributes
    void init();

    //Carga la textura
    void load_texture(const char* ruta);
    GLuint ID;

    //Parametros de posicionamiento
    float _x, _y, _width, _height, _rotacion;

};

#endif 
