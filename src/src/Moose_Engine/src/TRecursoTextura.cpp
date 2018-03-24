#include "TRecursoTextura.h"

TRecursoTextura::TRecursoTextura(){}
TRecursoTextura::~TRecursoTextura(){}

void TRecursoTextura::SetNombre(char* nombre){
    _nombre = nombre; 
}

char* TRecursoTextura::GetNombre(){
    return _nombre;
}

void TRecursoTextura::cargarFichero(char* nombre){}