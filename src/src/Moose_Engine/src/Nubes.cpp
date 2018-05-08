#include "Nubes.h"
#include "SOIL.h"
#include "Shader.h"
#include "glm/ext.hpp"
#include <iostream>



Nubes::Nubes(Shader* _i_shader) : shader(_i_shader){

    init();
    load_texture();

    for (GLuint i = 0; i < 1; ++i)
        clouds.push_back(Nube(glm::vec3(61.5158, 12, 44.2914)));
}
 
Nubes::~Nubes() {
 
}
 
void Nubes::init(){
        glEnable(GL_BLEND);

        float _x = 0.5;
        float _y = 0.5;
        float _width = 0.5;
        float _height = 0.5;


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint amount = 1;
}


GLuint Nubes::load_texture() {
  
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
  //  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = SOIL_load_image("Skybox_Images/Nube.png", &width, &height, 0, SOIL_LOAD_RGBA);
    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data);

   glUniform1i(glGetUniformLocation(Shader::Program, "sprite"), 0);
    
}


void Nubes::update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado){
    _rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(grados), rotation);
    _escalado = glm::scale(escalado);
    _traslacion = glm::translate(position);
  
    ModelMatrix =  _traslacion * _rotacion * _escalado;
    glm::mat4 view = shader->getView();

   
    ModelMatrix[0][0] = view[0][0]; 
    ModelMatrix[1][0] = view[0][1];
    ModelMatrix[2][0] = view[0][2];

    ModelMatrix[0][1] = view[1][0];
    ModelMatrix[1][1] = view[1][1];
    ModelMatrix[2][1] = view[1][2];

    ModelMatrix[0][2] = view[2][0];
    ModelMatrix[1][2] = view[2][1];
    ModelMatrix[2][2] = view[2][2];

    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(grados), rotation);
    ModelMatrix = glm::scale(ModelMatrix, escalado);
}



void Nubes::draw(){
        
        // Use additive blending to give it a 'glow' effect
    glDepthMask(false);
    // Don't forget to reset to default blending mode
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->use(particulas);
   
    for (Nube particle : this->clouds)
    {
      
        glDisable(GL_CULL_FACE);
        
        glm::mat4 projection = shader->getProjection();
        glm::mat4 view = shader->getView();
        
        update_model_matrix(particle.Position, 0, glm::vec3(0,0,1), glm::vec3(3,3,1));
        
        glm::mat4 MVP = projection*view*ModelMatrix;      

        
        GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
        GLfloat aColor = 0.5 + ((rand() % 100) / 100.0f);
         glm::vec4 Color(1.0, 1.0, 1.0, 1);
        

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform4fv(glGetUniformLocation(Shader::Program, "color"), 1, glm::value_ptr(Color));

        glUniform1i(glGetUniformLocation(Shader::Program, "sprite"), 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ID);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glEnable(GL_CULL_FACE);


        
    }
    // Don't forget to reset to default blending mode
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       glDepthMask(true);


}


