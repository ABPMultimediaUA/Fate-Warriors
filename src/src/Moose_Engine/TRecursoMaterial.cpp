#include "TRecursoMaterial.h"

TRecursoMaterial::TRecursoMaterial(){

}
TRecursoMaterial::TRecursoMaterial(aiMaterial* _i_material){
    _material=_i_material;
}
TRecursoMaterial::~TRecursoMaterial(){

}

void TRecursoMaterial::SetNombre(char* nombre){
    _nombre = nombre;
}

char* TRecursoMaterial::GetNombre(){
    return _nombre;
}


void TRecursoMaterial::cargarFichero(char* nombre){}