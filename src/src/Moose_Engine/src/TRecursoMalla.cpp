#include "TRecursoMalla.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

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

TRecursoMalla::TRecursoMalla(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        Preparar_mesh();
}
TRecursoMalla::~TRecursoMalla(){
    vertices.clear();
    indices.clear();
    textures.clear();
}

char* TRecursoMalla::GetNombre(){
    
}

void TRecursoMalla::SetNombre(char* nombre){
    std::cout<<"Le pongo el nombre "<<nombre<<"\n";
}
void TRecursoMalla::draw(){
    // bind appropriate textures 
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
         else if(name == "texture_height")
		    number = std::to_string(heightNr++); // transfer unsigned int to stream
												 // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(0, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    // draw mesh
    //_i_shader->setMat4("model", model);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    //glActiveTexture(GL_TEXTURE0);
}
void TRecursoMalla::Preparar_mesh(){

    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() *sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // set the vertex attribute pointers

    
    // vertex Positions
   glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    glBindVertexArray(0);
}
void TRecursoMalla::cargarFichero(char* nombre){
    /*Assimp::Importer importer;
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
    }*/
    //DoTheSceneProcessing(scene);
   //ShaderSource* shad;
   //preparar un shader para esto
}