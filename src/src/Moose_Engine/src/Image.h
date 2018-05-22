#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glm/glm.hpp>

#include "src/Moose_Engine/src/Shader.h"

class Shader;


class Image{
public:
    // Constructor
    Image(Shader* shader, int numTexturas, const char* ruta, const char* ruta2, const char* ruta3, const char* ruta4, float x, float y, float width, float height); 
    void setSelected(int selected);
    bool getSelected();
    ~Image();
    // Render all particles
    void Draw();
    void setSizeX(float sizeX); //0-> tamaño original, 1 -> reduccion 100%
private:
    //controla si se dibuja o no la version seleccionada de la imagen
    int _selected;
    float _sizeX; 
    // Render state
    Shader* shader;
    //buffers para las imagenes
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // inicializacion de los buffers y atributos de vertices
    void init();

    //funciones para la carga de hasta 4 texturas por objeto Image
    void load_texture(const char* ruta);
    void load_texture2(const char* ruta);
    void load_texture3(const char* ruta);
    void load_texture4(const char* ruta);
    GLuint ID,ID2,ID3,ID4;

    float _x, _y, _width, _height;

};

#endif 
