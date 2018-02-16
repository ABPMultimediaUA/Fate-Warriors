#include "Evento_musica.h"
#include "FMOD/fmod_errors.h"
#include <iostream>
void Evento_musica::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
Evento_musica::Evento_musica(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys): Evento_sonido(_i_ruta,sys){
    ERRCHECK( FMOD_Studio_EventDescription_CreateInstance(_evento, &_instancia) );

}
Evento_musica::~Evento_musica(){
    ERRCHECK( FMOD_Studio_EventInstance_Release(_instancia ));
}
void Evento_musica::start(){
    FMOD_STUDIO_PLAYBACK_STATE state;
    //(*state)=FMOD_STUDIO_PLAYBACK_STOPPING;
    ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(_instancia,&state));
    if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
        ERRCHECK( FMOD_Studio_EventInstance_Start(_instancia) );
    }
        //ERRCHECK( _instancia->start() );
    //return _i_play;
}
void Evento_musica::stop(){
    ERRCHECK(FMOD_Studio_EventInstance_Stop(_instancia, FMOD_STUDIO_STOP_IMMEDIATE));
}
void Evento_musica::pause(){
    ERRCHECK(FMOD_Studio_EventInstance_SetPaused ( _instancia, true ));
}
void Evento_musica::quit_pause(){
    ERRCHECK(FMOD_Studio_EventInstance_SetPaused ( _instancia, false ));
}