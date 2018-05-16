#ifndef MAPA_H
#define MAPA_H
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Enum_Texturas.h"

class Shader;
class Image_Map;
class Mapa
{
public:
    // Constructor
    Mapa(Shader* shader);
    ~Mapa();

    Image_Map* anyadir_elemento_al_mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo);
    void eliminar_elemento_mapa(Image_Map* objeto_a_eliminar);
    // Render all particles
    void Draw();

private:
    // State
    std::vector<Image_Map*> elementos_menu;
   
    // Render state
    Shader* shader;
    const char* Imagenes[Vegeta_count];

};

#endif 