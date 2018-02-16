#include "Evento_sonido.h"
#include "FMOD/fmod_errors.h"
#include <iostream>
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)
void Evento_sonido::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
Evento_sonido::Evento_sonido(std::string _i_ruta, FMOD_STUDIO_SYSTEM *sys){
    _evento=NULL;
    _instancia=nullptr;
    std::cout<<_i_ruta<<std::endl;
    ERRCHECK( FMOD_Studio_System_GetEvent(sys, _i_ruta.c_str(), &_evento) );
}
Evento_sonido::~Evento_sonido(){

}


void Evento_sonido::start(){
   
    if(_instancia==nullptr){
    ERRCHECK( FMOD_Studio_EventDescription_CreateInstance(_evento, &_instancia) );
    /*FMOD_STUDIO_PLAYBACK_STATE *state=nullptr;
    ERRCHECK( _instancia->getPlaybackState(state) );
    std::cout<<state<<std::endl;
    if(is_playing()){
        std::cout<<"algo"<<std::endl;
    }*/
    ERRCHECK( FMOD_Studio_EventInstance_Start(_instancia) );
 
    // Release will clean up the instance when it completes
    ERRCHECK( FMOD_Studio_EventInstance_Release(_instancia) );
    _instancia=nullptr;
    }
}

void Evento_sonido::set_position(float _i_x, float _i_y, float _i_z){
    FMOD_3D_ATTRIBUTES *attrib=nullptr;
    ERRCHECK(FMOD_Studio_EventInstance_Get3DAttributes(_instancia, attrib));
    FMOD_VECTOR vec;
    vec.x=_i_x;
    vec.y=_i_y;
    vec.z=_i_z;
    attrib->position=vec;
    ERRCHECK(FMOD_Studio_EventInstance_Set3DAttributes(_instancia, attrib));
}

