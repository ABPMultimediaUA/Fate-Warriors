#include "Evento_pasos.h"
Evento_pasos::Evento_pasos(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){

}
Evento_pasos::~Evento_pasos(){

}
void Evento_pasos::start(){
    Evento_sonido::start();
}