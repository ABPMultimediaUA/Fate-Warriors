#include "Evento_sonido.h"
#include "FMOD/fmod_errors.h"
#include <iostream>

void Evento_sonido::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
Evento_sonido::Evento_sonido(std::string _i_ruta, FMOD::Studio::System *sys){
    _evento=NULL;
    _instancia=NULL;
    ERRCHECK( sys->getEvent(_i_ruta.c_str(), &_evento) );
}
Evento_sonido::~Evento_sonido(){

}


void Evento_sonido::start(){
    ERRCHECK( _evento->createInstance(&_instancia) );

    ERRCHECK( _instancia->start() );

    // Release will clean up the instance when it completes
    ERRCHECK( _instancia->release() );

}
void Evento_sonido::stop(){
    ERRCHECK(_instancia->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
}
void Evento_sonido::pause(){
    ERRCHECK(_instancia -> setPaused ( true ));
}
void Evento_sonido::quit_pause(){
    ERRCHECK(_instancia -> setPaused ( false ));
}
void Evento_sonido::set_volume(float _i_vol){
    ERRCHECK(_instancia -> setVolume ( _i_vol ));
}
/*void Evento_sonido::set_gain(float _i_gantz){
    ERRCHECK(_instancia -> setGain ( _i_gantz ));
}*/
void Evento_sonido::set_position(float _i_x, float _i_y, float _i_z){
    FMOD_3D_ATTRIBUTES *attrib;
    ERRCHECK(_instancia -> get3DAttributes ( attrib ));;
    FMOD_VECTOR vec;
    vec.x=_i_x;
    vec.y=_i_y;
    vec.z=_i_z;
    attrib->position=vec;
    ERRCHECK(_instancia -> set3DAttributes ( attrib ));
}
/*bool Evento_sonido::is_playing(){
    bool _i_play;
    ERRCHECK(_instancia -> isPlaying (&_i_play));
    return _i_play;
}*/
