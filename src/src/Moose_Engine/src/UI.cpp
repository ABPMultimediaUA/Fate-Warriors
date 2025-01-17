#include "UI.h"
#include "Image.h"

//#include "stdint.h"

UI::UI(){
    _tiene_llave = false;
    _tipo_control = 0;
}

UI::~UI(){

    if(_img_llave != nullptr)
        delete _img_llave;

    for(u_int16_t i = 0; i<_lista_imagenes.size() - 1; i++){
        delete _lista_imagenes[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_pausa.size(); i++){
        delete _lista_imagenes_pausa[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_config.size(); i++){
        delete _lista_imagenes_config[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_config_2.size(); i++){
        delete _lista_imagenes_config_2[i];
    }

    for(u_int16_t i = 0; i < _lista_imagenes_hud.size(); i++){
        delete _lista_imagenes_hud[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_fin_lose.size(); i++){
        delete _lista_imagenes_fin_lose[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_fin_win.size(); i++){
        delete _lista_imagenes_fin_win[i];
    }

    for(u_int16_t i = 0; i<_lista_imagenes_carga.size(); i++){
        delete _lista_imagenes_carga[i];
    }
}

Image* UI::crear_imagen(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, ruta, x, y, width, height);
    _lista_imagenes.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_pausa(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, ruta, x, y, width, height);
    _lista_imagenes_pausa.push_back(imagen);
    return imagen;
}


Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, ruta, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 3, ruta, ruta2, ruta3, ruta, x, y, width, height);
    _lista_imagenes_hud.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagenHUD_llave(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _img_llave = imagen;
    return imagen;
}


Image* UI::crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, ruta2, x, y, width, height);
    _lista_imagenes_config.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_config.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 3, ruta, ruta2, ruta3, ruta3, x, y, width, height);
    _lista_imagenes_config.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 3, ruta, ruta2, ruta3, ruta3, x, y, width, height);
    _lista_imagenes_config_2.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_2(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, ruta, x, y, width, height);
    _lista_imagenes_config_2.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_2(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_config_2.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, const char* ruta4, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 4, ruta, ruta2, ruta3, ruta4, x, y, width, height);
    _lista_imagenes_config_3.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, const char* ruta3, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 3, ruta, ruta2, ruta3, ruta3, x, y, width, height);
    _lista_imagenes_config_3.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_config_3(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta2, ruta2, x, y, width, height);
    _lista_imagenes_config_3.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_win(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_win.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_win(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_win.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_lose(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_lose.push_back(imagen);
    return imagen;
}

Image* UI::crear_imagen_fin_lose(Shader* shader, const char* ruta, const char* ruta2, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 2, ruta, ruta2, ruta, ruta, x, y, width, height);
    _lista_imagenes_fin_lose.push_back(imagen);
    return imagen;
}


Image* UI::crear_imagen_pantalla_carga(Shader* shader, const char* ruta, float x, float y, float width, float height){
    Image* imagen = new Image(shader, 1, ruta, ruta, ruta, ruta, x, y, width, height);
    _lista_imagenes_carga.push_back(imagen);
    return imagen;
}

//dibujar menu del juego
void UI::drawMenu(uint8_t opcion){
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

    for(u_int16_t i = 1; i<_lista_imagenes.size() - 1; i++){
        _lista_imagenes[i]->Draw();
    }
}

void UI::drawMenuFondo(uint8_t _opcion) {
    _lista_imagenes[0]->Draw();
}

void UI::drawMenuLogo(uint8_t _opcion) {
    _lista_imagenes[_lista_imagenes.size() - 1]->Draw();
}

void UI::drawAyudaControles(){
    if(_tipo_control == 0)
        _lista_imagenes_carga[0]->Draw();
    else
        _lista_imagenes_carga[7]->Draw();
}

void UI::drawFiltroPausa(){
    _lista_imagenes_carga[5]->Draw();
}

void UI::drawFiltroLose(){
    _lista_imagenes_carga[6]->Draw();
}

void UI::drawFiltroWin(){
    _lista_imagenes_carga[5]->Draw();
}

//dibujar menu del juego
void UI::drawMenuPausa(uint8_t opcion){
    //actualizar las texturas de las imagenes del menu (seleccionadas / no seleccionadas)
    //en funcion de la opcion de menu recibida por parametro
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

void UI::drawMenuConfigSubmenu1(){
    for(u_int16_t i = 0; i<_lista_imagenes_config.size(); i++){
            _lista_imagenes_config[i]->Draw();
    }

    //desactivar la textura de seleccion en los menus 2 y 3 
    _lista_imagenes_config_2[0]->Draw();
    _lista_imagenes_config_3[0]->Draw();
}

void UI::drawMenuConfigSubmenu2(){
    for(u_int16_t i = 0; i<_lista_imagenes_config_2.size(); i++){
            _lista_imagenes_config_2[i]->Draw();
    }

    //desactivar la textura de seleccion en los menus 1 y 3 
    _lista_imagenes_config[0]->Draw();
    _lista_imagenes_config_3[0]->Draw();
}

void UI::drawMenuConfigSubmenu3(){
    for(u_int16_t i = 0; i<_lista_imagenes_config_3.size(); i++){
            _lista_imagenes_config_3[i]->Draw();
    }

    //desactivar la textura de seleccion en los menus 1 y 2 
    _lista_imagenes_config[0]->Draw();
    _lista_imagenes_config_2[0]->Draw();
}

//dibujar menu de config
void UI::setConfigSubmenu1(uint8_t opcion){
    //estado inicial de la seccion
    _lista_imagenes_config[0]->setSelected(3);
    _lista_imagenes_config[1]->setSelected(1);
    _lista_imagenes_config[2]->setSelected(1);
    _lista_imagenes_config[3]->setSelected(1);
    _lista_imagenes_config[4]->setSelected(1);
    _lista_imagenes_config[5]->setSelected(1);
    _lista_imagenes_config[6]->setSelected(1);
    
    _lista_imagenes_config_2[0]->setSelected(1);
    _lista_imagenes_config_3[0]->setSelected(1);
    //cambiar la textura de la imagen seleccionada
    switch(opcion){
        case 0:     
                    _lista_imagenes_config[0]->setSelected(2);
                    break;

        case 1:     
                    _lista_imagenes_config[1]->setSelected(2);
                    break;

        case 2:     
                    _lista_imagenes_config[2]->setSelected(2);
                    break;
        
        case 3:     
                    _lista_imagenes_config[3]->setSelected(2);
                    break;

        case 4:     
                    _lista_imagenes_config[4]->setSelected(2);
                    break;
            
        case 5:     
                    _lista_imagenes_config[5]->setSelected(2);
                    break;

        case 6:     
                    _lista_imagenes_config[6]->setSelected(2);
                    break;

        default:    
                    break;
    }
}

//dibujar menu de config
void UI::setConfigSubmenu2(uint8_t opcion){
    //estado inicial de la seccion
    _lista_imagenes_config_2[0]->setSelected(3);
    _lista_imagenes_config_2[1]->setSelected(1);
    _lista_imagenes_config_2[2]->setSelected(1);
    
    _lista_imagenes_config[0]->setSelected(1);
    _lista_imagenes_config_3[0]->setSelected(1);

    //cambiar la textura de la imagen seleccionada
    switch(opcion){
        case 5:     
                    _lista_imagenes_config_2[0]->setSelected(2);
                    break;

        case 6:     
                    _lista_imagenes_config_2[1]->setSelected(2);
                    break;

        case 7:     
                    _lista_imagenes_config_2[2]->setSelected(2);
                    break;
        default:    
                    break;
    }
}

void UI::setConfigSubmenu3(uint8_t opcion){
    //estado inicial de la seccion
    _lista_imagenes_config_3[0]->setSelected(3);
    _lista_imagenes_config_3[1]->setSelected(1);
    _lista_imagenes_config_3[2]->setSelected(1);
    _lista_imagenes_config_3[3]->setSelected(1);
    _lista_imagenes_config_3[4]->setSelected(1);
    
    _lista_imagenes_config[0]->setSelected(1);
    _lista_imagenes_config_2[0]->setSelected(1);

    //cambiar la textura de la imagen seleccionada
    switch(opcion){
        case 8:     
                    _lista_imagenes_config_3[0]->setSelected(2);
                    break;

        case 9:     
                    _lista_imagenes_config_3[1]->setSelected(2);
                    break;

        case 10:     
                    _lista_imagenes_config_3[2]->setSelected(2);
                    break;

        case 11:     
                    _lista_imagenes_config_3[3]->setSelected(2);
                    break;

        case 12:     
                    _lista_imagenes_config_3[4]->setSelected(2);
                    break;
        
        default:    
                    break;
    }
}

//dibujar menu del juego
void UI::drawMenuFinWin(uint8_t opcion){
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
    
    drawAyudaControles();
}

//dibujar menu del juego
void UI::drawMenuFinLose(uint8_t opcion){
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
    
    drawAyudaControles();
}

/*

void UI::crear_mapa(Shader* shader){

}
*/

//dibujar HUD y elementos durante el gameplay
void UI::drawHUD(){
    uint8_t _tam = _lista_imagenes_hud.size();
    for(u_int16_t i = 0; i < _tam; i++){
        _lista_imagenes_hud[i]->Draw();
    }
    //_mapa->Draw();
}


void UI::set_escala_vida(float escala){
    _lista_imagenes_hud[1]->setSizeX(escala);      //sabemos que es la 1 porque la barra de vida es la 1 en el hud
                                                   //la imagen 0 corresponde con la barra gris de fondo
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
    _lista_imagenes_config[6]->setSizeX(_escala); 
}

void UI::set_escala_sfx(float escala){
    float _escala = escala/9;;
    _lista_imagenes_config[8]->setSizeX(_escala); 
}

void UI::set_escala_voz(float escala){
    float _escala = escala/9;;
    _lista_imagenes_config[10]->setSizeX(_escala); 
}

void UI::set_escala_sonido_menu(float escala){
    float _escala = escala/9;
    _lista_imagenes_config[12]->setSizeX(_escala); 
}

void UI::set_eje_x(bool ejeX){
    if(ejeX == false){
        _lista_imagenes_config_2[3]->setSelected(1);
    }
    else{
        _lista_imagenes_config_2[3]->setSelected(2);
    }
}

void UI::set_eje_y(bool ejeY){
    if(ejeY == false){
        _lista_imagenes_config_2[4]->setSelected(1);
    }
    else{
        _lista_imagenes_config_2[4]->setSelected(2);
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
    _lista_imagenes_carga[1]->Draw();

    if(_tipo_control == 0)
        _lista_imagenes_carga[3]->Draw();
    else
        _lista_imagenes_carga[8]->Draw();

    drawAyudaControles();
}

void UI::render_partida_cargada() {
    _lista_imagenes[0]->Draw();
    _lista_imagenes_carga[4]->Draw();

    if(_tipo_control == 0) {
        _lista_imagenes_carga[2]->Draw();
        _lista_imagenes_carga[3]->Draw();
    }
    else {
        _lista_imagenes_carga[8]->Draw();
        _lista_imagenes_carga[9]->Draw();
    }

    drawAyudaControles();
}

void UI::setVsync(bool activar){
    if(activar){
        _lista_imagenes_config_3[6]->setSelected(2);
    }
    else{
        _lista_imagenes_config_3[6]->setSelected(1);
    }
}

void UI::set_resolution(uint8_t opcion){
    switch (opcion){
        case 0: _lista_imagenes_config_3[5]->setSelected(1);
                break;
        
        case 1: _lista_imagenes_config_3[5]->setSelected(2);
                break;

        case 2: _lista_imagenes_config_3[5]->setSelected(3);
                break;

        case 3: _lista_imagenes_config_3[5]->setSelected(4);
                break;

    }
}

void UI::setFullScreen(bool activar){
    if(activar){
        _lista_imagenes_config_3[7]->setSelected(2);
    }
    else{
        _lista_imagenes_config_3[7]->setSelected(1);
    }
}

void UI::set_texturas(uint8_t opcion){
    switch (opcion){
        case 0: _lista_imagenes_config_3[8]->setSelected(1);
                break;

        case 1: _lista_imagenes_config_3[8]->setSelected(2);
                break;

        case 2: _lista_imagenes_config_3[8]->setSelected(3);
                break;
    }
}