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
    glm::vec2 Position;
    glm::vec4 Color;
    GLint ID_textura;
    GameObject_Visual(float x, float y, GLint textura) : ID_textura(textura), Position(glm::vec2(x,y)), Color(1.0f){ }
};

class Mapa
{
public:
    // Constructor
    Mapa(Shader* shader);
    ~Mapa();

    GameObject_Visual* anyadir_elemento_al_mapa(float x, float y, Texture_ID_Map tipo);
    void eliminar_elemento_mapa(GameObject_Visual* objeto_a_eliminar);
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