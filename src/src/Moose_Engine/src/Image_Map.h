#ifndef IMAGE_MAP_H
#define IMAGE_MAP_H
#include <vector>

#include <glm/glm.hpp>

#include "src/Moose_Engine/src/Shader.h"

class Shader;


// Image acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class Image_Map{
public:
    // Constructor
    Image_Map(Shader* shader, float x, float y, float width, float height); 
    ~Image_Map();
    // Render all particles
    void Draw();
    void setSizeX(float sizeX); //0-> tamaño original, 1 -> reduccion 100%
    void setTextureposition(float x, float y);
private:
    //controla si se dibuja o no la version seleccionada de la imagen
    int _selected;
    float _sizeX; 
    // Render state
    Shader* shader;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // Initializes buffer and vertex attributes
    void init();
    void load_texture(const char* ruta);
    GLuint ID;

    float _x, _y, _width, _height;

};

#endif 
