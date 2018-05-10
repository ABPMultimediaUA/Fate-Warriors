#include "UI.h"
#include "Image.h"

//#include "stdint.h"

UI::UI(){

}

UI::~UI(){

}

Image* UI::crear_imagen(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, x, y, width, height);
    _lista_imagenes.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_pausa(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, x, y, width, height);
    _lista_imagenes_pausa.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 3, ruta, ruta2, ruta3, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, x, y, width, height);
    _lista_imagenes_config.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_config.push_back(imagen);
    return imagen;
}




//dibujar menu del juego
void UI::drawMenu(uint16_t opcion){
    switch(opcion){
        case 0:     _lista_imagenes[1]->setSelected(2);
                    _lista_imagenes[2]->setSelected(1);
                    _lista_imagenes[3]->setSelected(1);
                    break;

        case 1:     _lista_imagenes[1]->setSelected(1);
                    _lista_imagenes[2]->setSelected(2);
                    _lista_imagenes[3]->setSelected(1);
                    break;

        case 2:     _lista_imagenes[1]->setSelected(1);
                    _lista_imagenes[2]->setSelected(1);
                    _lista_imagenes[3]->setSelected(2);
                    break;
        
        default:    _lista_imagenes[1]->setSelected(2);
                    _lista_imagenes[2]->setSelected(1);
                    _lista_imagenes[3]->setSelected(1);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes.size(); i++){
        _lista_imagenes[i]->Draw();
    }
}

//dibujar menu del juego
void UI::drawMenuPausa(uint16_t opcion){
    switch(opcion){
        case 0:     _lista_imagenes_pausa[0]->setSelected(2);
                    _lista_imagenes_pausa[1]->setSelected(1);
                    _lista_imagenes_pausa[2]->setSelected(1);
                    break;

        case 1:     _lista_imagenes_pausa[0]->setSelected(1);
                    _lista_imagenes_pausa[1]->setSelected(2);
                    _lista_imagenes_pausa[2]->setSelected(1);
                    break;

        case 2:     _lista_imagenes_pausa[0]->setSelected(1);
                    _lista_imagenes_pausa[1]->setSelected(1);
                    _lista_imagenes_pausa[2]->setSelected(2);
                    break;
        
        default:    _lista_imagenes_pausa[0]->setSelected(2);
                    _lista_imagenes_pausa[1]->setSelected(1);
                    _lista_imagenes_pausa[2]->setSelected(1);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes_pausa.size(); i++){
        _lista_imagenes_pausa[i]->Draw();
    }
}

//dibujar menu de config
void UI::drawMenuConfig(uint16_t opcion){
    
    switch(opcion){
        case 0:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    break;

        case 1:     _lista_imagenes_config[0]->setSelected(1);
                    _lista_imagenes_config[1]->setSelected(2);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    
                    break;

        case 2:     _lista_imagenes_config[0]->setSelected(1);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(2);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    break;
        
        case 3:     _lista_imagenes_config[0]->setSelected(1);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(2);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    break;

        case 4:     _lista_imagenes_config[0]->setSelected(1);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(2);
                    _lista_imagenes_config[5]->setSelected(1);
                    break;
            
        case 5:     _lista_imagenes_config[0]->setSelected(1);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(2);
                    break;

        default:    _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes_config.size(); i++){
        _lista_imagenes_config[i]->Draw();
    }
}

//dibujar HUD y elementos durante el gameplay
void UI::drawHUD(){
    
    for(u_int16_t i = 0; i<_lista_imagenes_hud.size(); i++){
        _lista_imagenes_hud[i]->Draw();
    }
}

void UI::set_escala_vida(float escala){
    _lista_imagenes_hud[1]->setSizeX(escala);      //sabemos que es la 1 porque la barra de vida es la 1 en el hud
    if(escala>=0.66){
        _lista_imagenes_hud[1]->setSelected(1); //barra verde
    }

    else if(escala<0.66 && escala>=0.33){
        _lista_imagenes_hud[1]->setSelected(2); //barra amarilla
    }

    else{
        _lista_imagenes_hud[1]->setSelected(3); //barra roja
    }
}