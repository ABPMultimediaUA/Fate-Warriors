#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TRecursoTextura.h"
#include "TRecursoMaterial.h"
#include "TRecursoModelado.h"
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
    /*glm::vec3 Tangent;
    glm::vec3 Bitangent;*/
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
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

TRecurso* TGestorRecursos::getRecursoModelo(char* nombre, std::vector<TRecursoMalla*> &_i_modelos){
    TRecurso* rec;
    TRecursoMalla* rec_aux;
    rec=getRecurso(nombre);

    if(rec==nullptr){
        std::string s(nombre);
        cargarModelo(s,_i_modelos);
        _recursos.back()->SetNombre(nombre);
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
    directory = path.substr(0, path.find_last_of('/'));
    cargarNodo(scene->mRootNode, scene, _i_modelos, path);
    int width, height, nrChannels;
    
    unsigned int texture1, texture2;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //stbi_set_flip_vertically_on_load(true);
    /*unsigned char *data = stbi_load("lel.jpg", &width, &height, &nrChannels, 0); 
    if(!data){
        std::cout<<"añlsdkjfañlsdkjfñalksdjf"<<std::endl;
        exit(0);
    }
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    stbi_image_free(data);*/
}

void TGestorRecursos::cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos, std::string path){
    // process each mesh located at the current nodo
    for(unsigned int i = 0; i < nodo->mNumMeshes; i++){
        // the nodo object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, nodo is just to keep stuff organized (like relations between nodos).
        aiMesh* mesh = scene->mMeshes[nodo->mMeshes[i]];
        _i_modelos.push_back(cargarMalla(mesh, scene, path));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodos
    for(unsigned int i = 0; i < nodo->mNumChildren; i++){
        cargarNodo(nodo->mChildren[i], scene, _i_modelos, path);
    }
    _recursos.push_back(new TRecursoModelado());
}

TRecursoMalla* TGestorRecursos::cargarMalla(aiMesh *mesh, const aiScene *scene, std::string path){
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
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
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
    /*TRecursoMaterial* _material=new TRecursoMaterial(material);
    _material->SetNombre((char*)(path+std::to_string((int)mesh->mMaterialIndex)).c_str());*/

    //maps
    //diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //shininess maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_shininess");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    //devolver la malla creada a partir de los datos obtenidos*/
    TRecursoMalla* malla= new TRecursoMalla(vertices, indices, textures);
    return malla;
}
std::vector<Texture> TGestorRecursos::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), this->directory, true);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}
unsigned int TGestorRecursos::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{

    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width=0, height=0, nrComponents=0;
    //unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    /*std::cout <<nrComponents<<std::endl;
    std::cout <<width<<"         "<<height<<std::endl;
    std::cout <<"data:   "<<data<<std::endl;*/
    if (data)
    {
        GLenum format;
        if (nrComponents == 1){
            format = GL_RED;
        }
        else if (nrComponents == 3){
            format = GL_RGB;
        }
        else if (nrComponents == 4){
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
//preguntar acerca del glGenerateMimmap
//p
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}