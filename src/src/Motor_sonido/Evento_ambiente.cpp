#include "Evento_ambiente.h"
Evento_ambiente::Evento_ambiente(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){
     ERRCHECK( FMOD_Studio_EventDescription_CreateInstance(_evento, &_instancia) );

}
Evento_ambiente::~Evento_ambiente(){
    ERRCHECK( FMOD_Studio_EventInstance_Release(_instancia ));
}
void Evento_ambiente::start(){
    FMOD_STUDIO_PLAYBACK_STATE state;
    //(*state)=FMOD_STUDIO_PLAYBACK_STOPPING;
    ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(_instancia,&state));
    if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
        ERRCHECK( FMOD_Studio_EventInstance_Start(_instancia) );
    }
        //ERRCHECK( _instancia->start() );
    //return _i_play;
}
void Evento_ambiente::stop(){
    ERRCHECK(FMOD_Studio_EventInstance_Stop(_instancia, FMOD_STUDIO_STOP_IMMEDIATE));
}
void Evento_ambiente::pause(){
    ERRCHECK(FMOD_Studio_EventInstance_SetPaused ( _instancia, true ));
}
void Evento_ambiente::quit_pause(){
    ERRCHECK(FMOD_Studio_EventInstance_SetPaused ( _instancia, false ));
}