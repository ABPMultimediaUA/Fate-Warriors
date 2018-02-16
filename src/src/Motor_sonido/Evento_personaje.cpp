#include "Evento_personaje.h"
Evento_personaje::Evento_personaje(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){

}
Evento_personaje::~Evento_personaje(){

}
void Evento_personaje::start(){
    Evento_sonido::start();
}