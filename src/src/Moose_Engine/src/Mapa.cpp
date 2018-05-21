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

   Imagenes[Enum_Llave]              =  load_texture("Imagenes_HUD/Minimapa/Llave.png");
   Imagenes[Enum_Mapa]               =  load_texture("Imagenes_HUD/Minimapa/mapa.png");
   Imagenes[Enum_Player]             =  load_texture("Imagenes_HUD/Minimapa/Player.png");
   Imagenes[Enum_Enemigo]            =  load_texture("Imagenes_HUD/Minimapa/Enemy.png");
   Imagenes[Enum_Puerta]             =  load_texture("Imagenes_HUD/Minimapa/Cerradura.png");
   Imagenes[Enum_Interruptor]        =  load_texture("Imagenes_HUD/Minimapa/Interruptor.png");
   Imagenes[Enum_Puerta_Pincho]      =  load_texture("Imagenes_HUD/Minimapa/Puerta_Pincho.png");
   Imagenes[Enum_Puerta_Tiempo]      =  load_texture("Imagenes_HUD/Minimapa/Puerta_Tiempo.png");
   Imagenes[Enum_Puerta_Desactivada] =  load_texture("Imagenes_HUD/Minimapa/Puerta_Desactivada.png");
   
   anyadir_elemento_al_mapa(420/2, 560/2, 420, 560,Enum_Mapa);
      
}


Mapa::~Mapa(){
 for (short i = 0; i < elementos_menu.size(); i++) {
    delete elementos_menu[i];
  }
  elementos_menu.clear();
}

/* Busca y elimina un elemento del mapa */

void Mapa::eliminar_elemento_mapa(Image_Map* objeto_a_eliminar){

    std::vector<Image_Map*>::iterator it;
    it = std::find(elementos_menu.begin(), elementos_menu.end(), objeto_a_eliminar);
    
    if ( it != elementos_menu.end()){
        elementos_menu.erase(it);
        delete objeto_a_eliminar;
    }

}

/* Añade un nuevo elemento al mapa */
Image_Map* Mapa::anyadir_elemento_al_mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo){
    Image_Map* objeto_nuevo = new Image_Map(shader, Imagenes[tipo], x, y, ancho, alto);
    elementos_menu.push_back(objeto_nuevo);
    return objeto_nuevo;
}

// Render all particles
void Mapa::Draw()
{    

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

}


GLuint Mapa::load_texture(const char* ruta){
    GLuint ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    
    unsigned char *data = SOIL_load_image(ruta, &width, &height, 0, SOIL_LOAD_RGBA);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data);
    
    glUniform1i(glGetUniformLocation(Shader::Program, "texture1"), ID);
    return ID;
}
