#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoTextura.h"
#include "TRecursoMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
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

TRecurso* TGestorRecursos::getRecursoMalla(char* nombre, std::vector<TRecursoMalla*> &_i_modelos){
    TRecurso* rec;
    TRecursoMalla* rec_aux;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        std::string s(nombre);
        cargarModelo(s,_i_modelos);
    }
    return rec;
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
void TGestorRecursos::cargarModelo(std::string &path, std::vector<TRecursoMalla*> &_i_modelos){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){//si no es cero
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // coger el path
    _path = path.substr(0, path.find_last_of('/'));
    cargarNodo(scene->mRootNode, scene, _i_modelos);
}

void TGestorRecursos::cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos){
    // process each mesh located at the current node
    for(unsigned int i = 0; i < nodo->mNumMeshes; i++){
        // the nodo object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, nodo is just to keep stuff organized (like relations between nodos).
        aiMesh* mesh = scene->mMeshes[nodo->mMeshes[i]];
        _i_modelos.push_back(cargarMalla(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodos
    for(unsigned int i = 0; i < nodo->mNumChildren; i++){
        cargarNodo(nodo->mChildren[i], scene, _i_modelos);
    }
}

TRecursoMalla* TGestorRecursos::cargarMalla(aiMesh *mesh, const aiScene *scene){
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
   /* // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.push_back(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.push_back(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.push_back(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.push_back(textures.end(), heightMaps.begin(), heightMaps.end());
    */
    //devolver la malla creada a partir de los datos obtenidos
    TRecursoMalla* modelado= new TRecursoMalla(vertices, indices, textures);
    return modelado;
}