#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoMaterial.h"
#include "TRecursoModelado.h"
#include "TRecursoAnimacion.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


TGestorRecursos* TGestorRecursos::_instancia = 0;

TGestorRecursos* TGestorRecursos::get_instancia(){
    if(_instancia == 0){
        _instancia= new TGestorRecursos();
    }
    return _instancia;
}
TGestorRecursos::TGestorRecursos(){}
TGestorRecursos::~TGestorRecursos(){
    for(auto it = _recursos.begin(); it!=_recursos.end(); it++){ //itera por el vector eliminando
        delete *it;
    }
}

void TGestorRecursos::setCalidad(uint8_t _calidad){
    variableCalidad = _calidad;
}

TRecurso* TGestorRecursos::getRecurso(const char* nombre){//funcion de busqueda del recurso
    TRecurso* rec;
    for(uint16_t i=0; i<_recursos.size();i++){
        if(nombre==_recursos[i]->GetNombre()){
            rec = _recursos[i];
            return rec;
        }
    }
    return nullptr;
}
TRecursoAnimacion* TGestorRecursos::getRecursoAnim(const char* nombre){
    TRecurso* rec;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        std::string s(nombre);
        std::vector<TRecursoModelado*> modelos;
        cargarAnim(s,modelos);
        return static_cast<TRecursoAnimacion*>(_recursos.back());
    }
    return static_cast<TRecursoAnimacion*>(rec);
}

TRecursoModelado* TGestorRecursos::getRecursoModelo(const char* nombre){
    TRecurso* rec;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        
        std::string s(nombre);
        cargarModelo(s);
        _recursos.back()->SetNombre((char*)nombre);
        return static_cast<TRecursoModelado*>(_recursos.back());
    }
    return static_cast<TRecursoModelado*>(rec);
}



TRecursoMaterial* TGestorRecursos::getRecursoMaterial(char* nombre){
    TRecurso* rec;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        std::string s(nombre);
        rec = new TRecursoMaterial(nombre);
        _recursos.push_back(rec);
        return static_cast<TRecursoMaterial*>(rec);
    }

    return static_cast<TRecursoMaterial*>(rec);
}
void TGestorRecursos::cargarAnim(std::string &path, std::vector<TRecursoModelado*> &_i_modelados){
    Assimp::Importer importer;
    uint16_t cont=0;
    std::string path2 = path.substr(path.find_last_of('_')+1, path.size()-path.find_last_of('_')-1);
    std::string aux;
    std::string path_obj;
    std::string path_text;
    //segun la calidad que se desee, se cargan las animaciones de una carpeta u otra
    if(variableCalidad == 1){
        aux="animaciones/"+path2+"/"+path+"/"+path;
        path_obj=aux;
        path_text="animaciones/"+path2+"/";
    }
    else if(variableCalidad == 2){
        aux="animaciones_medium/"+path2+"/"+path+"/"+path;
        path_obj=aux;
        path_text="animaciones_medium/"+path2+"/";
    }
    else{
        aux="animaciones_high/"+path2+"/"+path+"/"+path;
        path_obj=aux;
        path_text="animaciones_high/"+path2+"/";
    }
    
    path_obj+="."+std::to_string(0)+'0'+'0'+std::to_string(cont)+".obj";
        
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    while(!scene && cont<200){//bucle para encontrar el primer numero de la animacion
        scene = importer.ReadFile(path_obj, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        ++cont;
        path_obj=aux;
        if(cont>=10){//eleccion de la cantidad de 0 a poner
            if(cont>=100){
                path_obj+="."+std::to_string(0)+std::to_string(cont)+".obj";
            }else{
                path_obj+="."+std::to_string(0)+'0'+std::to_string(cont)+".obj";
            }
        }else{
            path_obj+="."+std::to_string(0)+'0'+'0'+std::to_string(cont)+".obj";
        }
    }
    while(scene){//bucle para cargar todos los modelos de la animacion
        cargarModelo(path_obj, scene, _i_modelados, path_text);
        ++cont;
        path_obj=aux;
        if(cont>=10){//busqueda de la cantidad de 0 que tiene
            if(cont>=100){
                path_obj+="."+std::to_string(0)+std::to_string(cont)+".obj";
            }else{
                path_obj+="."+std::to_string(0)+'0'+std::to_string(cont)+".obj";
            }
        }else{
            path_obj+="."+std::to_string(0)+'0'+'0'+std::to_string(cont)+".obj";
        }
        scene = importer.ReadFile(path_obj, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        
    }
    _recursos.push_back(new TRecursoAnimacion(_i_modelados,path.c_str()));
}
void TGestorRecursos::cargarModelo(std::string &path, const aiScene* scene, std::vector<TRecursoModelado*> &_i_modelados, const std::string &path_text){

    std::vector<TRecursoMalla*> _modelos;
    cargarNodo(scene->mRootNode, scene, _modelos, path_text);
    int width, height, nrChannels;
    unsigned int texture1, texture2;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    TRecursoModelado* modelado = new TRecursoModelado(_modelos,path.c_str());
    glm::vec3 Vmax,Vmin,BB;
    //paso final en la creacion del bounding box de una animacion
    for(auto it = _modelos.begin(); it!=_modelos.end(); it++){ 
        Vmax.x=std::max(Vmax.x,(*it)->get_max().x);
        Vmax.y=std::max(Vmax.y,(*it)->get_max().y);
        Vmax.z=std::max(Vmax.z,(*it)->get_max().z);
        Vmin.x=std::min(Vmin.x,(*it)->get_min().x);
        Vmin.y=std::min(Vmin.y,(*it)->get_min().y);
        Vmin.z=std::min(Vmin.z,(*it)->get_min().z);
    }
    BB.x=Vmax.x-Vmin.x;
    BB.y=Vmax.y-Vmin.y;
    BB.z=Vmax.z-Vmin.z;
    modelado->set_BB(BB);
    _i_modelados.push_back(modelado);
}
void TGestorRecursos::cargarModelo(std::string &path){
    std::vector<TRecursoMalla*> _modelos;
    Assimp::Importer importer;
    
    std::string aux;
    const aiScene* scene;
    //segun la calidad que se desee, se cargan los modelos de una carpeta u otra
    if(variableCalidad == 1){
            //calidad de textura normal
            aux="models/";
            aux+=path+"/"+path+".obj";//cambio de ruta para coger el obj
            scene = importer.ReadFile(aux, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){//si no es cero
                std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                return;
            }
            aux="models/"+path+"/";//cambio de ruta para coger la ruta de la textura
    }
    else if(variableCalidad == 2){
            //calidad de textura media
            aux="models_medium/";
            aux+=path+"/"+path+".obj";//cambio de ruta para coger el obj
            scene = importer.ReadFile(aux, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){//si no es cero
                std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                return;
            }
            aux="models_medium/"+path+"/";//cambio de ruta para coger la ruta de la textura
    }
    else{
            //calidad de texturas epica
            aux="models_high/";
            aux+=path+"/"+path+".obj";//cambio de ruta para coger el obj
            scene = importer.ReadFile(aux, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){//si no es cero
                std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                return;
            }
            aux="models_high/"+path+"/";//cambio de ruta para coger la ruta de la textura
    }
    // coger el path
    cargarNodo(scene->mRootNode, scene, _modelos, aux);
    int width, height, nrChannels;
    
    unsigned int texture1, texture2;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    TRecursoModelado* modelado = new TRecursoModelado(_modelos,path.c_str());
    glm::vec3 Vmax,Vmin,BB;

    //paso final en la creacion del bounding box de una animacion
    for(auto it = _modelos.begin(); it!=_modelos.end(); it++){ 
        Vmax.x=std::max(Vmax.x,(*it)->get_max().x);
        Vmax.y=std::max(Vmax.y,(*it)->get_max().y);
        Vmax.z=std::max(Vmax.z,(*it)->get_max().z);
        Vmin.x=std::min(Vmin.x,(*it)->get_min().x);
        Vmin.y=std::min(Vmin.y,(*it)->get_min().y);
        Vmin.z=std::min(Vmin.z,(*it)->get_min().z);
    }
    BB.x=Vmax.x-Vmin.x;
    BB.y=Vmax.y-Vmin.y;
    BB.z=Vmax.z-Vmin.z;
    modelado->set_BB(BB);
    _recursos.push_back(modelado);
}

void TGestorRecursos::cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, const std::string& path){
    //funcion recursiva para la carga de los diferentes nodos de assimp
    for(unsigned int i = 0; i < nodo->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[nodo->mMeshes[i]];
        _i_modelos.push_back(cargarMalla(mesh, scene, path));
    }
    for(unsigned int i = 0; i < nodo->mNumChildren; i++){
        cargarNodo(nodo->mChildren[i], scene, _i_modelos, path);
    }
}

TRecursoMalla* TGestorRecursos::cargarMalla(aiMesh *mesh, const aiScene *scene,const std::string path){
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TRecursoMaterial*> textures;
    
    glm::vec3 Vmax;
    glm::vec3 Vmin;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {//carga de los vertices y busqueda de los maximimos y minimos
        Vertex vertex;
        glm::vec3 vector; 
        
        vector.x = mesh->mVertices[i].x * -1;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        Vmax.x=std::max(Vmax.x,vector.x);
        Vmax.y=std::max(Vmax.y,vector.y);
        Vmax.z=std::max(Vmax.z,vector.z);
        Vmin.x=std::min(Vmin.x,vector.x);
        Vmin.y=std::min(Vmin.y,vector.y);
        Vmin.z=std::min(Vmin.z,vector.z);
        vertex.Position = vector;
        // normales
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // coordenadas de textura
        if(mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
   aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 
   //mapas
    //diffuse
    std::vector<TRecursoMaterial*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "_diffuse", path);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    //specular
    std::vector<TRecursoMaterial*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "_specular", path);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    //ambiente
    std::vector<TRecursoMaterial*> abmientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "_ambient", path);
    textures.insert(textures.end(), abmientMaps.begin(), abmientMaps.end()); 

    //normales
    std::vector<TRecursoMaterial*> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "_normales", path);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());


    //devolver la malla creada a partir de los datos obtenidos*/
    TRecursoMalla* malla= new TRecursoMalla(vertices, indices, textures);
    malla->set_min(Vmin);
    malla->set_max(Vmax);
    return malla;
}
std::vector<TRecursoMaterial*> TGestorRecursos::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string& path)
{//el nombre del material esta basado en la ruta,el material y el tipo de material que es(ambient,normal...)
    std::vector<TRecursoMaterial*> materiales;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {//carga de los materiales
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string aux(path);
        aux+=str.C_Str();
        std::string aux2(aux+typeName);
        TRecursoMaterial* material=getRecursoMaterial((char*)aux2.c_str());
        materiales.push_back(material);
    }
    return materiales;
}
