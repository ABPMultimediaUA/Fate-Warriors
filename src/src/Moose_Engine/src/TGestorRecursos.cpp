#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoTextura.h"
#include "TRecursoMaterial.h"


TGestorRecursos::TGestorRecursos(){}
TGestorRecursos::~TGestorRecursos(){
    for(auto it = _recursos.begin(); it!=_recursos.end(); it++){ //itera por el vector eliminando
        delete *it;
    }
}

TRecurso* TGestorRecursos::getRecurso(char* nombre){
    TRecurso* rec;
    for(uint16_t i=0; i<_recursos.size();i++){
        if(nombre==_recursos[i]->GetNombre()){
            rec = _recursos[i];
            return rec;
        }
    }
    return nullptr;
}

TRecurso* TGestorRecursos::getRecursoMalla(char* nombre){
    TRecurso* rec;
    TRecursoMalla* rec_aux;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        /*rec_aux = new TRecursoMalla();
        rec_aux ->cargarFichero(nombre);
        _recursos.push_back(rec_aux);*/
    }
    return rec_aux;
}

TRecurso* TGestorRecursos::getRecursoTextura(char* nombre){
    TRecurso* rec;
    TRecursoTextura* rec_aux;
    rec=getRecurso(nombre);

    if(rec_aux==nullptr){
        rec_aux = new TRecursoTextura();
        rec_aux ->cargarFichero(nombre);
        _recursos.push_back(rec_aux);
    }

    return rec_aux;
}

TRecurso* TGestorRecursos::getRecursoMaterial(char* nombre){
    TRecurso* rec;
    TRecursoMaterial* rec_aux;
    rec=getRecurso(nombre);

    if(rec_aux==nullptr){
        rec_aux = new TRecursoMaterial();
        rec_aux ->cargarFichero(nombre);
        _recursos.push_back(rec_aux);
    }

    return rec_aux;
}