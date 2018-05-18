#include "TRecursoMalla.h"
#include "TRecursoMaterial.h"
#include "Shader.h"


#include <iostream>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

TRecursoMalla::TRecursoMalla(std::vector<Vertex> _i_vertices, 
    std::vector<unsigned int> _i_indices, std::vector<TRecursoMaterial*> _i_textures)
    : vertices( std::move(_i_vertices) ), indices( std::move(_i_indices) ), textures( std::move(_i_textures) )
    {
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

std::string TRecursoMalla::GetNombre(){
    
}

void TRecursoMalla::SetNombre(std::string nombre){
    
}
void TRecursoMalla::draw(Shader* shader){
    for(uint8_t i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i); //activar la textura correspondiente 
        std::string number;
        std::string name = textures[i]->Get_type();
        if(name == "_diffuse"){
            shader->setInt("Material.Diffuse",i);//pasar la textura difusa
        }	
		else if(name == "_specular"){
            shader->setInt("Material.Specular",i);//pasar la texutra especular
            shader->setInt("Material.Shininess",i);
        }	
        else if(name == "_normales"){
            shader->setInt("Material.Normal",i);//pasar el brillo
        }
        //bind texture
        glBindTexture(GL_TEXTURE_2D, textures[i]->Get_id());
    }
    
    // dibujar mesh
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
void TRecursoMalla::Preparar_mesh(){

    // crear buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // pasar los datos a los buffers
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
glm::vec3 TRecursoMalla::get_max(){
        return _max;
}
void TRecursoMalla::set_max(glm::vec3 _i_max){
    _max=_i_max;
}
glm::vec3 TRecursoMalla::get_min(){
        return _min;
}
void TRecursoMalla::set_min(glm::vec3 _i_min){
    _min=_i_min;
}