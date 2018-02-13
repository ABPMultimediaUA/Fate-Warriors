#include "TRecursoMalla.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

TRecursoMalla::TRecursoMalla(){}
TRecursoMalla::~TRecursoMalla(){}

char* TRecursoMalla::GetNombre(){
    
}

void TRecursoMalla::SetNombre(char* nombre){
    std::cout<<"Le pongo el nombre "<<nombre<<"\n";
}


void TRecursoMalla::cargarFichero(char* nombre){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( nombre,
    aiProcess_CalcTangentSpace      |
    aiProcess_Triangulate           |
    aiProcess_JoinIdenticalVertices |
    aiProcess_SortByPType            );
    if(!scene){
        std::cout<<"Esta mierda no funciona porque esto no vale na (hablando de manjaro) y: "<<importer.GetErrorString()<<std::endl;
        exit(0);
    }
    
    SetNombre(nombre);
    //DoTheSceneProcessing(scene);
   
}