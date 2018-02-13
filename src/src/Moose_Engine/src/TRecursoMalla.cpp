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
        std::cout<<"La malla no se ha cargado correctamente: "<<importer.GetErrorString()<<std::endl;
        exit(0);
    }
    
    SetNombre(nombre);
    uint16_t n_mesh=scene->mNumMeshes;
    while(n_mesh){
        n_mesh--;
        aiMesh* mesh = scene->mMeshes[n_mesh];
        vertices = &mesh->mVertices[0][0];
        normales = mesh->mNormals[0][0];
        texturas = mesh->mTextureCoords[0][0][0];
        nTriangulos += mesh->mNumFaces;
    }
    //DoTheSceneProcessing(scene);
   //ShaderSource* shad;
   //preparar un shader para esto
}