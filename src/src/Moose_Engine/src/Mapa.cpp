#include "Mapa.h"
#include "SOIL.h"
#include "Shader.h"
#include "Image_Map.h"
#include "glm/ext.hpp"
#include <iostream>



Mapa::Mapa(Shader* shader)
    : shader(shader)
{

    Imagenes[Enum_Llave] =  "Imagenes_HUD/Llave_Silueta.png";
    Imagenes[Enum_Mapa] =  "Imagenes_HUD/mapa.png";
    Imagenes[Enum_Player] =  "";
    
   anyadir_elemento_al_mapa(0,0,1280,720,Enum_Mapa);
   anyadir_elemento_al_mapa(780,0,50,50,Enum_Llave);
  // anyadir_elemento_al_mapa(200,200,200,200,Enum_Player);
      
}


Mapa::~Mapa(){
}

void Mapa::eliminar_elemento_mapa(Image_Map* objeto_a_eliminar){
/*
    std::vector<GameObject_Visual>::iterator it;
    it = std::find(elementos_menu.begin(), elementos_menu.end(), objeto_a_eliminar);
    if ( it != elementos_menu.end()){
        elementos_menu.erase(it);
        delete objeto_a_eliminar;
    }
    */
}

Image_Map* Mapa::anyadir_elemento_al_mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo){
    Image_Map* objeto_nuevo = new Image_Map(shader, Imagenes[tipo], x, y, ancho, alto);
    elementos_menu.push_back(objeto_nuevo);
    return objeto_nuevo;
}

// Render all particles
void Mapa::Draw()
{    
        // Use additive blending to give it a 'glow' effect
   // Don't forget to reset to default blending mode
    
    glDisable(GL_CULL_FACE);
    for (int a =0; a < elementos_menu.size(); a++)
    {
        elementos_menu[a]->Draw();
    }
    glEnable(GL_CULL_FACE);
    // Don't forget to reset to default blending mode
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

