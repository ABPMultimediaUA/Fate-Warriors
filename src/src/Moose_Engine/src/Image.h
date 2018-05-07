#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glm/glm.hpp>

#include "src/Moose_Engine/src/Shader.h"

class Shader;


// Image acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class Image{
public:
    // Constructor
    Image(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height); 
    void setSelected(bool selected);
    bool getSelected();
    ~Image();
    // Render all particles
    void Draw();
    void setSizeX(float sizeX); //0-> tamaño original, 1 -> reduccion 100%
private:
    //controla si se dibuja o no la version seleccionada de la imagen
    bool _selected;
    float _sizeX; 
    // Render state
    Shader* shader;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // Initializes buffer and vertex attributes
    void init();
    void load_texture(const char* ruta);
    void load_texture2(const char* ruta);
    GLuint ID,ID2;

    float _x, _y, _width, _height;

};

#endif 
