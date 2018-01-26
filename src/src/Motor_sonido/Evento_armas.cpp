#include "Evento_armas.h"
Evento_armas::Evento_armas(std::string _i_ruta, FMOD::Studio::System *sys): Evento_sonido(_i_ruta,sys){

}
Evento_armas::~Evento_armas(){
    
}
void Evento_armas::start(){
    Evento_sonido::start();
}