#include "TRecursoModelado.h"
#include "TRecursoMalla.h"

TRecursoModelado::TRecursoModelado(std::vector<TRecursoMalla*> _i_mallas, const char* _i_nombre):
    _mallas(std::move(_i_mallas)){
    _nombre=_i_nombre;
}

TRecursoModelado::~TRecursoModelado(){

}

void TRecursoModelado::SetNombre(std::string nombre){
    _nombre = nombre;
}

std::string TRecursoModelado::GetNombre(){
    return _nombre;
}
void TRecursoModelado::draw(Shader* _i_shader){
    for(std::vector<TRecursoMalla*>::iterator it = _mallas.begin(); it != _mallas.end(); it++){
        (*it)->draw(_i_shader);
    }
}
void TRecursoModelado::set_BB(glm::vec3 _i_BB){
    _BB=_i_BB;
}
glm::vec3 TRecursoModelado::get_BB(){
    return _BB;
}
