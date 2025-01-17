/* Creado y modificado a partir de:
https://learnopengl.com/Advanced-OpenGL/Cubemaps 
*/

#include "Skybox.h"

#include "Shader.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
 
#include "SOIL.h"

#include <GLFW/glfw3.h>

Skybox::Skybox() {
    GLfloat skyboxVertices[] = {
        // Positions de los vertices         
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
 
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
 
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
 
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
 
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
 
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };
    // Setup skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (GLfloat), (GLvoid*) 0);
    glBindVertexArray(0);
    // Cubemap (Skybox)
    faces.push_back("Skybox_Images/left.jpg"); //left
    faces.push_back("Skybox_Images/right.jpg"); //right
    faces.push_back("Skybox_Images/top.jpg"); //top
    faces.push_back("Skybox_Images/bottom.jpg"); //bottom
    faces.push_back("Skybox_Images/back.jpg"); //back   
    faces.push_back("Skybox_Images/front.jpg"); //front
    cubemapTexture = loadCubemap(faces);
}
 
Skybox::~Skybox() {
 
}

/* Carga la lista de imagenes de las caras */ 

GLuint Skybox::loadCubemap(std::vector<const GLchar*> faces) {
    
    GLuint textureID;
    glGenTextures(1, &textureID);
 
    
    int width, height;
    unsigned char* image;
 
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < faces.size(); i++) {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);

        
    if (!image) {
        std::cout << "Failed to load texture: " << sizeof(image) << std::endl;
    }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
 
    return textureID;
}

/* Dibujado del skybox */

void Skybox::draw(Shader* _i_shader, glm::mat4 view, glm::mat4 projection){
        
    // Draw skybox as last
    glDepthFunc(GL_LEQUAL); // Change depth function so depth test passes when values are equal to depth buffer's content
    glDisable(GL_CULL_FACE);
    _i_shader->use(eSkybox);
    glm::mat4 n_view = glm::mat4(glm::mat3(view)); 
    glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "view"), 1, GL_FALSE, glm::value_ptr(n_view));
    glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(Shader::Program, "skybox"), 0); //Pasa 
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS); // Set depth function back to default
        
    //_i_shader->use(Default);

}


