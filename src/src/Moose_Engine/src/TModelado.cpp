#include "TModelado.h"
#include "TRecursoMalla.h"
#include "TGestorRecursos.h"
#include "Shader.h"
#include <iostream>



TModelado::TModelado(const char* path){
    _t_matriz = glm::mat4(1.0f);
    std::string s(path);
    leerModelado(s);
}
TModelado::~TModelado(){
    _mallas.clear();
}
void TModelado::beginDraw(Shader* _i_shader){
    draw(_i_shader);
    std::cout<<"ID ------"<<_ID<<"\n";
}

void TModelado::draw(Shader* _i_shader){
    _i_shader->setMat4("model", matriz);
    for(std::vector<TRecursoMalla*>::iterator it = _mallas.begin(); it != _mallas.end(); it++){
        (*it)->draw();
    }
}

void TModelado::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";    
}
void TModelado::leerModelado(std::string &path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    gRec->cargarModelo(path, _mallas);
    
    /*
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){//si no es cero
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // coger el path
    _path = path.substr(0, path.find_last_of('/'));
    cargarNodo(scene->mRootNode, scene);
    */
}