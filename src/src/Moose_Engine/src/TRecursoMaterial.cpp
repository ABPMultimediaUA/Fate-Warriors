#include "TRecursoMaterial.h"
#include "stb_image.h"
#include <iostream>
#include <GLFW/glfw3.h>
TRecursoMaterial::TRecursoMaterial(std::string nombre){
    //_nombre=&nombre[0];
    _path=nombre;
    std::string aux(nombre);
    std::string type = aux.substr(aux.find_last_of('_')+1, aux.size()-aux.find_last_of('_')-1);
    std::string path = aux.substr(0,aux.find_last_of('_'));
    cargarFichero(path.c_str());
    //std::cout << _nombre << "   id: "<<_id<<std::endl;
}

TRecursoMaterial::~TRecursoMaterial(){

}

void TRecursoMaterial::SetNombre(std::string nombre){
    //_nombre = nombre;
}

std::string TRecursoMaterial::GetNombre(){
    /*std::cout<< "_id: "<<_id<<std::endl;
    std::cout <<_path<<std::endl;
    std::cout << _path << "   id: "<<_id<<std::endl;*/
    return _path;
}


void TRecursoMaterial::cargarFichero(const char* path){

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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    _id = textureID;
}