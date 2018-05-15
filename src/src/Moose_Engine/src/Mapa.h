#ifndef MAPA_H
#define MAPA_H
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;
class Image_Map;

enum Texture_ID_Map {
    Enum_Mapa = 0,
    Enum_Llave,
    Enum_Player,
    Vegeta_count
};


class Mapa
{
public:
    // Constructor
    Mapa(Shader* shader);
    ~Mapa();

    Image_Map* anyadir_elemento_al_mapa(float x, float y, Texture_ID_Map tipo);
    void eliminar_elemento_mapa(Image_Map* objeto_a_eliminar);
    void actualizar_elemento_mapa(Image_Map* objeto_a_modificar);
    // Render all particles
    void Draw();

private:
    // State
    std::vector<Image_Map*> elementos_menu;
   
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