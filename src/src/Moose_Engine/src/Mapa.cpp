#include "Mapa.h"
#include "SOIL.h"
#include "Shader.h"
#include "Image_Map.h"
#include "glm/ext.hpp"
#include <iostream>
#include <algorithm>


Mapa::Mapa(Shader* shader)
    : shader(shader)
{

   Imagenes[Enum_Llave] =  "Imagenes_HUD/Minimapa/Llave.png";
   Imagenes[Enum_Mapa] =  "Imagenes_HUD/Minimapa/mapa.png";
   Imagenes[Enum_Player] =  "Imagenes_HUD/Minimapa/Player.png";
   Imagenes[Enum_Enemigo] =  "Imagenes_HUD/Minimapa/Player.png";
   Imagenes[Enum_Puerta] =  "Imagenes_HUD/Minimapa/Cerradura.png";
   Imagenes[Enum_Interruptor] =  "Imagenes_HUD/Minimapa/Interruptor.png";
   Imagenes[Enum_Puerta_Pincho] =  "Imagenes_HUD/Minimapa/Puerta_Pincho.png";
   Imagenes[Enum_Puerta_Tiempo] =  "Imagenes_HUD/Minimapa/Puerta_Tiempo.png";
   Imagenes[Enum_Puerta_Desactivada] =  "Imagenes_HUD/Minimapa/Puerta_Desactivada.png";
   
   

   anyadir_elemento_al_mapa(420/2, 560/2, 420, 560,Enum_Mapa);
      
}


Mapa::~Mapa(){
 for (short i = 0; i < elementos_menu.size(); i++) {
    delete elementos_menu[i];
  }
  elementos_menu.clear();
}

void Mapa::eliminar_elemento_mapa(Image_Map* objeto_a_eliminar){

    std::vector<Image_Map*>::iterator it;
   it = std::find(elementos_menu.begin(), elementos_menu.end(), objeto_a_eliminar);
    if ( it != elementos_menu.end()){
        elementos_menu.erase(it);
        delete objeto_a_eliminar;
    }

    
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
        shader->use(texturas_menu);
        if(a!=1)
        elementos_menu[a]->Draw();
    }

    shader->use(emapa);
    elementos_menu[1]->update_rotacion();
    elementos_menu[1]->Draw();
    glEnable(GL_CULL_FACE);
    // Don't forget to reset to default blending mode
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

