#include "Evento_escenario.h"
Evento_escenario::Evento_escenario(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){

}
Evento_escenario::~Evento_escenario(){

}
void Evento_escenario::start(){
    Evento_sonido::start();
}