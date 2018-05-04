#include "UI.h"
#include "Image.h"

//#include "stdint.h"

UI::UI(){

}

UI::~UI(){

}

Image* UI::crear_imagen(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, ruta, ruta2, x, y, width, height);
    _lista_imagenes.push_back(imagen);
    return imagen;
}

//dibujar menu del juego
void UI::drawMenu(uint16_t opcion){
    switch(opcion){
        case 0:     _lista_imagenes[1]->setSelected(true);
                    _lista_imagenes[2]->setSelected(false);
                    _lista_imagenes[3]->setSelected(false);
                    break;

        case 1:     _lista_imagenes[1]->setSelected(false);
                    _lista_imagenes[2]->setSelected(true);
                    _lista_imagenes[3]->setSelected(false);
                    break;

        case 2:     _lista_imagenes[1]->setSelected(false);
                    _lista_imagenes[2]->setSelected(false);
                    _lista_imagenes[3]->setSelected(true);
                    break;
        
        default:    _lista_imagenes[1]->setSelected(true);
                    _lista_imagenes[2]->setSelected(false);
                    _lista_imagenes[3]->setSelected(false);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes.size(); i++){
        _lista_imagenes[i]->Draw();
    }
}

//dibujar HUD y elementos durante el gameplay
void UI::drawUI(){

}