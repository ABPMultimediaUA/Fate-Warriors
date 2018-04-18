#include "Evento_ambiente.h"
Evento_ambiente::Evento_ambiente(std::string _i_ruta, FMOD::Studio::System *sys): Evento_sonido(_i_ruta,sys){
    ERRCHECK( _evento->createInstance(&_instancia) );

}
Evento_ambiente::~Evento_ambiente(){
    ERRCHECK( _instancia->release() );
}
void Evento_ambiente::start(){
    FMOD_STUDIO_PLAYBACK_STATE state;
    //(*state)=FMOD_STUDIO_PLAYBACK_STOPPING;
    ERRCHECK(_instancia->getPlaybackState(&state));
    if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
        ERRCHECK( _instancia->start() );
    }
        //ERRCHECK( _instancia->start() );
    //return _i_play;
}
void Evento_ambiente::stop(){
    ERRCHECK(_instancia->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
}
void Evento_ambiente::pause(){
    ERRCHECK(_instancia -> setPaused ( true ));
}
void Evento_ambiente::quit_pause(){
    ERRCHECK(_instancia -> setPaused ( false ));
}