#include "TRecursoModelado.h"
#include "TRecursoMalla.h"

TRecursoModelado::TRecursoModelado(std::vector<TRecursoMalla*> _i_mallas, const char* _i_nombre):
    _mallas(std::move(_i_mallas)){
    _nombre=(char*)_i_nombre;
}

TRecursoModelado::~TRecursoModelado(){

}

void TRecursoModelado::SetNombre(char* nombre){
    _nombre = nombre;
}

char* TRecursoModelado::GetNombre(){
    return _nombre;
}
void TRecursoModelado::draw(Shader* _i_shader){
    for(std::vector<TRecursoMalla*>::iterator it = _mallas.begin(); it != _mallas.end(); it++){
        (*it)->draw(_i_shader);
    }
}
