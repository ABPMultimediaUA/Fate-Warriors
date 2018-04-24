#include "Evento_pasos.h"
Evento_pasos::Evento_pasos(std::string _i_ruta, FMOD::Studio::System *sys): Evento_sonido(_i_ruta,sys){
    ERRCHECK( _evento->createInstance(&_instancia) );
}
Evento_pasos::~Evento_pasos(){
    ERRCHECK( _instancia->release() );
}
void Evento_pasos::start(){
    FMOD_STUDIO_PLAYBACK_STATE state;
    //(*state)=FMOD_STUDIO_PLAYBACK_STOPPING;
    ERRCHECK(_instancia->getPlaybackState(&state));
    if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
        ERRCHECK( _instancia->start() );
    }
}
void Evento_pasos::stop(){
    ERRCHECK(_instancia->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}