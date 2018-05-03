#include "TModeladoEscenario.h"
#include "TRecursoModelado.h"
#include "Shader.h"
TModeladoEscenario::TModeladoEscenario(const char* path):TModelado(path){

}
void TModeladoEscenario::draw(Shader * _i_shader){
    if(!_i_shader->check_program(sombras_proyectadas)){
        _i_shader->setModel(_matriz);
        _modelado->draw(_i_shader);
    }
}