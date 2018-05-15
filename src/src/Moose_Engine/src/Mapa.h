#ifndef MAPA_H
#define MAPA_H
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;

enum Texture_ID_Map {
    Enum_Mapa = 0,
    Enum_Llave,
    Enum_Player,
    Vegeta_count
};


// Represents a single particle and its state
struct GameObject_Visual {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;
    GLint ID_textura;
    GameObject_Visual(GLint textura) : ID_textura(textura), Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class Mapa
{
public:
    // Constructor
    Mapa(Shader* shader);
    ~Mapa();

    void anyadir_elemento_al_mapa();
    void eliminar_elemento_mapa();
    void actualizar_elemento_mapa(GameObject_Visual* objeto_a_modificar);
    // Render all particles
    void Draw();

private:
    // State
    std::vector<GameObject_Visual*> elementos_menu;
   
    // Render state
    Shader* shader;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
   
    // Initializes buffer and vertex attributes
    void init();
    // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    void load_texture(const char* ruta, Texture_ID_Map elemento);
    
 GLuint Imagenes[Vegeta_count];
    GLuint ID;

};

#endif 