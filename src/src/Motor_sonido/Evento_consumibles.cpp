#include "Evento_consumibles.h"
Evento_consumibles::Evento_consumibles(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){

}
Evento_consumibles::~Evento_consumibles(){

}
void Evento_consumibles::start(){
    Evento_sonido::start();
}