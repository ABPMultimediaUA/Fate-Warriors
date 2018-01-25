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
    _instancia=nullptr;
    std::cout<<_i_ruta<<std::endl;
    ERRCHECK( sys->getEvent(_i_ruta.c_str(), &_evento) );
}
Evento_sonido::~Evento_sonido(){

}


void Evento_sonido::start(){
   
    if(_instancia==nullptr){
    ERRCHECK( _evento->createInstance(&_instancia) );
    /*FMOD_STUDIO_PLAYBACK_STATE *state=nullptr;
    ERRCHECK( _instancia->getPlaybackState(state) );
    std::cout<<state<<std::endl;
    if(is_playing()){
        std::cout<<"algo"<<std::endl;
    }*/
    ERRCHECK( _instancia->start() );
 
    // Release will clean up the instance when it completes
    ERRCHECK( _instancia->release() );
    _instancia=nullptr;
    }
}

void Evento_sonido::set_position(float _i_x, float _i_y, float _i_z){
    FMOD_3D_ATTRIBUTES *attrib=nullptr;
    ERRCHECK(_instancia -> get3DAttributes ( attrib ));;
    FMOD_VECTOR vec;
    vec.x=_i_x;
    vec.y=_i_y;
    vec.z=_i_z;
    attrib->position=vec;
    ERRCHECK(_instancia -> set3DAttributes ( attrib ));
}

