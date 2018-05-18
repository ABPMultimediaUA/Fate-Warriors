#include "UI.h"
#include "Image.h"

#include <iostream>
//#include "stdint.h"

UI::UI(){
    _tiene_llave = false;
}

UI::~UI(){
    if(_img_llave != nullptr)
        delete _img_llave;
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

Image* UI::crear_imagenHUD_llave(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _img_llave = imagen;
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

Image* UI::crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, x, y, width, height);
    _lista_imagenes_config_2.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_2(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_config_2.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_win(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_win.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_win(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, x, y, width, height);
    _lista_imagenes_fin_win.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_lose(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_lose.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_lose(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, x, y, width, height);
    _lista_imagenes_fin_lose.push_back(imagen);
    return imagen;
}


Image* UI::crear_imagen_pantalla_carga(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_carga.push_back(imagen);
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

    for(u_int16_t i = 0; i<_lista_imagenes.size() - 1; i++){
        _lista_imagenes[i]->Draw();
    }
}

void UI::drawMenuLogo(uint16_t _opcion) {
    drawMenu(_opcion);
    _lista_imagenes[_lista_imagenes.size() - 1]->Draw();
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
        case 0:     
                    _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);

                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;

        case 1:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(2);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);
                    
                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;

        case 2:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(2);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);
                    
                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;
        
        case 3:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(2);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);
                    
                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;

        case 4:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(2);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);
                    
                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;
            
        case 5:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(2);
                    _lista_imagenes_config[6]->setSelected(1);
                    
                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;

        case 6:     _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(2);

                    _lista_imagenes_config_2[0]->setSelected(1);
                    break;

        case 7:     _lista_imagenes_config_2[0]->setSelected(2); //pagina de menu
                    _lista_imagenes_config_2[1]->setSelected(1); //resolucion
                    _lista_imagenes_config_2[2]->setSelected(1); //vsync
                    _lista_imagenes_config_2[3]->setSelected(1); //fullscreen

                    _lista_imagenes_config[0]->setSelected(1);
                    break;
                
        case 8:     _lista_imagenes_config_2[0]->setSelected(2);
                    _lista_imagenes_config_2[1]->setSelected(2);
                    _lista_imagenes_config_2[2]->setSelected(1);
                    _lista_imagenes_config_2[3]->setSelected(1);

                    _lista_imagenes_config[0]->setSelected(1);
                    break;
        
        case 9:     _lista_imagenes_config_2[0]->setSelected(2);
                    _lista_imagenes_config_2[1]->setSelected(1);
                    _lista_imagenes_config_2[2]->setSelected(2);
                    _lista_imagenes_config_2[3]->setSelected(1);

                    _lista_imagenes_config[0]->setSelected(1);
                    break;
        
        case 10:     _lista_imagenes_config_2[0]->setSelected(2);
                    _lista_imagenes_config_2[1]->setSelected(1);
                    _lista_imagenes_config_2[2]->setSelected(1);
                    _lista_imagenes_config_2[3]->setSelected(2);

                    _lista_imagenes_config[0]->setSelected(1);
                    break;

        default:    _lista_imagenes_config[0]->setSelected(2);
                    _lista_imagenes_config[1]->setSelected(1);
                    _lista_imagenes_config[2]->setSelected(1);
                    _lista_imagenes_config[3]->setSelected(1);
                    _lista_imagenes_config[4]->setSelected(1);
                    _lista_imagenes_config[5]->setSelected(1);
                    _lista_imagenes_config[6]->setSelected(1);
                    break;
    }

    if(opcion >= 0 && opcion < 7){
        for(u_int16_t i = 0; i<_lista_imagenes_config.size(); i++){
            _lista_imagenes_config[i]->Draw();
        }
            _lista_imagenes_config_2[0]->Draw();
    }

    else{
        for(u_int16_t i = 0; i<_lista_imagenes_config_2.size(); i++){
            _lista_imagenes_config_2[i]->Draw();
        }
            _lista_imagenes_config[0]->Draw();
    }

}

//dibujar menu del juego
void UI::drawMenuFinWin(uint16_t opcion){
    switch(opcion){
        case 0:     _lista_imagenes_fin_win[1]->setSelected(2);
                    _lista_imagenes_fin_win[2]->setSelected(1);
                    break;

        case 1:     _lista_imagenes_fin_win[1]->setSelected(1);
                    _lista_imagenes_fin_win[2]->setSelected(2);
                    break;
        
        default:    _lista_imagenes_fin_win[1]->setSelected(2);
                    _lista_imagenes_fin_win[2]->setSelected(1);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes_fin_win.size(); i++){
        _lista_imagenes_fin_win[i]->Draw();
    }
}

//dibujar menu del juego
void UI::drawMenuFinLose(uint16_t opcion){
    switch(opcion){
        case 0:     _lista_imagenes_fin_lose[1]->setSelected(2);
                    _lista_imagenes_fin_lose[2]->setSelected(1);
                    break;

        case 1:     _lista_imagenes_fin_lose[1]->setSelected(1);
                    _lista_imagenes_fin_lose[2]->setSelected(2);
                    break;
        
        default:    _lista_imagenes_fin_lose[1]->setSelected(2);
                    _lista_imagenes_fin_lose[2]->setSelected(1);
                    break;
    }

    for(u_int16_t i = 0; i<_lista_imagenes_fin_lose.size(); i++){
        _lista_imagenes_fin_lose[i]->Draw();
    }
}

/*

void UI::crear_mapa(Shader* shader){

}
*/

//dibujar HUD y elementos durante el gameplay
void UI::drawHUD(){
    uint16_t _tam = _lista_imagenes_hud.size();
    for(u_int16_t i = 0; i < _tam; i++){
        _lista_imagenes_hud[i]->Draw();
    }
    //_mapa->Draw();
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

void UI::set_escala_musica(float escala){
    float _escala = escala/9;;
    _lista_imagenes_config[8]->setSizeX(_escala); 
}

void UI::set_escala_sfx(float escala){
    float _escala = escala/9;;
    _lista_imagenes_config[10]->setSizeX(_escala); 
}

void UI::set_escala_voz(float escala){
    float _escala = escala/9;;
    _lista_imagenes_config[12]->setSizeX(_escala); 
}

void UI::set_escala_sonido_menu(float escala){
    float _escala = escala/9;
    _lista_imagenes_config[14]->setSizeX(_escala); 
}

void UI::set_eje_x(bool ejeX){
    if(ejeX == false){
        _lista_imagenes_config[15]->setSelected(1);
    }
    else{
        _lista_imagenes_config[15]->setSelected(2);
    }
}

void UI::set_eje_y(bool ejeY){
    if(ejeY == false){
        _lista_imagenes_config[16]->setSelected(1);
    }
    else{
        _lista_imagenes_config[16]->setSelected(2);
    }
}

void UI::set_tiene_llave(bool _i_tiene_llave){ 
    if(_tiene_llave != _i_tiene_llave) {
        _tiene_llave = _i_tiene_llave;

        Image* _aux = _img_llave;
        _img_llave = _lista_imagenes_hud[_lista_imagenes_hud.size()-1];
        _lista_imagenes_hud.pop_back();
        _lista_imagenes_hud.push_back(_aux);
    }
}

void UI::render_pantalla_carga() {
    _lista_imagenes[0]->Draw();
    _lista_imagenes_carga[0]->Draw();
}

void UI::render_partida_cargada() {
    _lista_imagenes[0]->Draw();
    _lista_imagenes_carga[1]->Draw();
}