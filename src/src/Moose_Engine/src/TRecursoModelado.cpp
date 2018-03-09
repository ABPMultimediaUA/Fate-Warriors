#include "TRecursoModelado.h"

TRecursoModelado::TRecursoModelado(){

}

TRecursoModelado::~TRecursoModelado(){

}

void TRecursoModelado::SetNombre(char* nombre){
    _nombre = nombre;
}

char* TRecursoModelado::GetNombre(){
    return _nombre;
}
