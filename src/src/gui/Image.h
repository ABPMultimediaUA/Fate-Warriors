#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glm/glm.hpp>

#include "../Moose_Engine/src/Shader.h"

class Shader;


// Image acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class Image{
public:
    // Constructor
    Image(Shader* shader, const char* texture);
    ~Image();
    // Render all particles
    void Draw();
private:

    // Render state
    Shader* shader;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // Initializes buffer and vertex attributes
    void init();
    void load_texture(const char* texture);

    GLuint ID;

};

#endif 
