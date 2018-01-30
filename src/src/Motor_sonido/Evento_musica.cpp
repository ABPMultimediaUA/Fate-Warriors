#include "Evento_musica.h"
Evento_musica::Evento_musica(std::string _i_ruta, FMOD::Studio::System *sys): Evento_sonido(_i_ruta,sys){
    ERRCHECK( _evento->createInstance(&_instancia) );

}
Evento_musica::~Evento_musica(){
    ERRCHECK( _instancia->release() );
}
void Evento_musica::start(){
    FMOD_STUDIO_PLAYBACK_STATE state;
    //(*state)=FMOD_STUDIO_PLAYBACK_STOPPING;
    ERRCHECK(_instancia->getPlaybackState(&state));
    if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
        ERRCHECK( _instancia->start() );
    }
        //ERRCHECK( _instancia->start() );
    //return _i_play;
}
void Evento_musica::stop(){
    ERRCHECK(_instancia->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}
void Evento_musica::pause(){
    ERRCHECK(_instancia -> setPaused ( true ));
}
void Evento_musica::quit_pause(){
    ERRCHECK(_instancia -> setPaused ( false ));
}