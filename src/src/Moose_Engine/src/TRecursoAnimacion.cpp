#include "TRecursoAnimacion.h"
#include "TRecursoModelado.h"
#include "Shader.h"
TRecursoAnimacion::TRecursoAnimacion(std::vector<TRecursoModelado*> _i_modelos, const char* _i_nombre):
    _modelos(std::move(_i_modelos)){
    _nombre=_i_nombre;
    
}
TRecursoAnimacion::~TRecursoAnimacion(){
    _modelos.clear();
}
void TRecursoAnimacion::draw(Shader* shader, uint8_t num){
    if(num<_modelos.size()){
        _modelos[num]->draw(shader);
    }
}
void TRecursoAnimacion::SetNombre(std::string nombre){
    _nombre = nombre;
}

std::string TRecursoAnimacion::GetNombre(){
    
    return _nombre;
}
glm::vec3 TRecursoAnimacion::get_BB(){
     return _modelos[0]->get_BB();
}