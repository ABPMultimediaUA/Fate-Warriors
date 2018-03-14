#include "TRecursoMalla.h"
#include "Shader.h"
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

TRecursoMalla::TRecursoMalla(std::vector<Vertex> vert, 
    std::vector<unsigned int> ind, std::vector<Texture> tex)
    : vertices( std::move(vert) ), indices( std::move(ind) ), textures( std::move(tex) )
    {
    //    this->vertices = vertices;
    //    this->indices = indices;
    //    this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        Preparar_mesh();
}
TRecursoMalla::~TRecursoMalla(){
    vertices.clear();
    indices.clear();
    textures.clear();
    const GLuint* VA=&VAO;
    const GLuint*VB=&VBO;
    const GLuint*EB=&EBO;

    glDeleteBuffers(1,VA);
    glDeleteBuffers(1,VB);
    glDeleteBuffers(1,EB);
}

char* TRecursoMalla::GetNombre(){
    
}

void TRecursoMalla::SetNombre(char* nombre){
    
}
void TRecursoMalla::draw(Shader* shader){
    for(uint8_t i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i); //activar la textura correspondiente 
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse"){
            shader->setInt("Material.Diffuse",i);//pasar la textura difusa
        }	
		else if(name == "texture_specular"){
            shader->setInt("Material.Specular",i);//pasar la texutra especular
        }	
        else if(name == "texture_shininess"){
            shader->setInt("Material.Shininess",i);//pasar el brillo
        }
        //bind texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    // draw mesh
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //std::cout<<"elementos: "<<(int)*std::max(indices.begin(),indices.end())<<std::endl;
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
void TRecursoMalla::Preparar_mesh(){

    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // load data into buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GL_UNSIGNED_INT), &indices[0], GL_STATIC_DRAW);


    
    // vertex Positions
   glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

}