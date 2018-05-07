

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "ParticleGenerator.h"
#include "SOIL.h"
#include "Shader.h"
#include "glm/ext.hpp"
#include <iostream>



ParticleGenerator::ParticleGenerator(Shader* shader,const char* texture, GLuint amount)
    : shader(shader), texture(texture), amount(amount)
{
    init();
    load_texture();
}




ParticleGenerator::~ParticleGenerator(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}



void ParticleGenerator::Reuse_Particles(GameObject &object, GLuint newParticles, glm::vec2 offset, GLint _direccion){
        // Add new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
                std::cout <<  _direccion << std::endl;

        this->respawnParticle(this->particles[unusedParticle], _direccion, offset);
    }
}






void ParticleGenerator::Update(GLfloat dt)
{
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i)
    {
        Particle &p = this->particles[i];
        p.Life -= dt; // reduce life
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            p.Position -= p.Velocity * dt; 
            p.Color.a -= dt * 2.5;
        }
    }
}

// Render all particles
void ParticleGenerator::Draw()
{
    // Use additive blending to give it a 'glow' effect
    glDepthMask(false);
    // Don't forget to reset to default blending mode
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->use(particulas);
        Update(2);
    
    for (Particle particle : this->particles)
    {
      if (particle.Life > 0.0f)
        {

        glDisable(GL_CULL_FACE);
        
        glm::mat4 projection = shader->getProjection();
        glm::mat4 view = shader->getView();
        
        update_model_matrix(particle.Position, 288, glm::vec3(0,0,1), glm::vec3(1,1,1));
        
        glm::mat4 MVP = projection*view*ModelMatrix;      

        GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
        GLfloat aColor = 0.5 + ((rand() % 100) / 100.0f);
        particle.Color = glm::vec4(1.0, 1.0, 1.0, 1);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
      //  glUniform4fv(glGetUniformLocation(Shader::Program, "color"), 1, glm::value_ptr(particle.Color));

        glUniform1i(glGetUniformLocation(Shader::Program, "sprite"), 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ID);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glEnable(GL_CULL_FACE);


        }
    }
    // Don't forget to reset to default blending mode
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       glDepthMask(true);


}

void ParticleGenerator::update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado){
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
}


void ParticleGenerator::load_texture(){
    
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
    unsigned char *data = SOIL_load_image("Skybox_Images/Opcion_1.png", &width, &height, 0, SOIL_LOAD_RGBA);
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



void ParticleGenerator::init()
{
        glEnable(GL_BLEND);

        float _x = 0.5;
        float _y = 0.5;
        float _width = 0.5;
        float _height = 0.5;


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         _x + _width,  _y,          0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
         _x + _width, _y - _height, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // bottom right
         _x, _y - _height,          0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
         _x,  _y,                   0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f // top left 
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


    // Create this->amount default particle instances
    for (GLuint i = 0; i < this->amount; ++i)

        this->particles.push_back(Particle( glm::vec3(61.5158, 12, 44.2914), glm::vec3(0,1,0) * 0.1f, 50));
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, GLint _direccion, glm::vec2 offset)
{
    GLfloat desp_x, desp_z;

	desp_z = cos((_direccion*std::acos(-1)/180));
    desp_x = sin((_direccion*std::acos(-1)/180));
           // std::cout << particle.Position.x << " " << particle.Position.y << " " << particle.Position.z << "\n " ;
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle.Position = glm::vec3(offset.x, 12, offset.y);
    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.Life = 50.0f;
    particle.Velocity = glm::vec3(0,1,0) * 0.1f;
    particle.Velocity.x = -desp_x * 0.5;
    particle.Velocity.z = -desp_z * 0.5;

}

