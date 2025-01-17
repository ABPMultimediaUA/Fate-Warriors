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
    
    //Elimina una imagen del mapa
    void eliminar_elemento_mapa(Image_Map* objeto_a_eliminar);
    
    //Activa/desactiva la visualizacion del mapa
    void activar_desactivar_minimapa();

    // Dibuja todos los elementos del mapa
    void Draw();

    /*Carga las texturas de los elementos del minimapa para luego reutilizar esa imagen en los demas elementos del minimapa*/
    GLuint load_texture(const char* ruta);

private:
    
    //Elementos del menu 
    std::vector<Image_Map*> elementos_menu;
   
    Shader* shader;
    
    bool activo;
    //Contiene la ruta de las imagenes
    GLuint Imagenes[Vegeta_count];

};

#endif 