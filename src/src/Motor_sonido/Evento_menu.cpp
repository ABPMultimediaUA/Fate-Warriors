#include "Evento_menu.h"
Evento_menu::Evento_menu(std::string _i_ruta, FMOD::Studio::System *sys): Evento_sonido(_i_ruta,sys){

}
Evento_menu::~Evento_menu(){

}
void Evento_menu::start(){
    Evento_sonido::start();
}