#include "UI.h"
#include "Image.h"

UI::UI(){

}

UI::~UI(){

}

Image* UI::crear_imagen(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, ruta, x, y, width, height);
    _lista_imagenes.push_back(imagen);
    return imagen;
}

//dibujar menu del juego
void UI::drawMenu(){
    for(u_int16_t i = 0; i<_lista_imagenes.size(); i++){
        _lista_imagenes[i]->Draw();
    }
}

//dibujar HUD y elementos durante el gameplay
void UI::drawUI(){

}