/* Basado y editado de (de orden de mas informacion a menos) BILLBOARDS :)
    https://learnopengl.com/In-Practice/2D-Game/Particles 
    https://www.3dgep.com/simulating-particle-effects-using-opengl/
    http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/billboards/
    http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/
    ...
*/

#include "ParticleGenerator.h"
#include "SOIL.h"
#include "Shader.h"
#include "glm/ext.hpp"
#include <iostream>

ParticleGenerator::ParticleGenerator(Shader* shader, GLuint amount)
    : shader(shader), amount(amount)
{
    init();
    load_texture();
}

ParticleGenerator::~ParticleGenerator(){
    /*Elimina el array de vertices y los buffers*/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void ParticleGenerator::Reuse_Particles(GLuint newParticles, glm::vec3 offset, GLint _direccion){
        // Add new particles 
    for (GLuint i = 0; i < 2; ++i)
    {
        GLfloat rVelocidad = 0.5 + ((rand() % 1000) / 100.0f);
        GLfloat altura = 5 + ((rand() % 100) / 20.0f);
        
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], _direccion, -1, glm::vec3(rVelocidad, 9.0,rVelocidad), glm::vec3(offset.x,altura, offset.z));
    }
}

void ParticleGenerator::Reuse_Particles_Ground(GLuint newParticles, glm::vec3 offset, GLint _direccion){
        // Add new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle_Active();
        if(unusedParticle!=-1)
        this->respawnParticle(this->particles[unusedParticle], _direccion, 4, glm::vec3(0.5f,-4.0,0.5f), offset, 1.75f, 0.6f,0.6f,0.6f);
    }
}

void ParticleGenerator::Update(GLfloat dt){

    // Update all particles
    for (GLuint i = 0; i < amount; ++i){
        Particle &p = particles[i];
        p.grados = rand() % 359;
        p.Life -= dt; // reduce life
        p.Scale += dt * p.Scale_Factor;
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            p.Position -= p.Velocity * dt; 
            if(p.Color.a  > 0)
            p.Color.a -= dt * .5;
            else{
                 p.Color.a = 0;
            }
        }
    }
}

// Dibuja las particulas
void ParticleGenerator::Draw()
{
    // Use additive blending to give it a 'glow' effect
    glDepthMask(false);
    // Don't forget to reset to default blending mode
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->use(particulas);
   
    for (Particle particle : this->particles){
        if (particle.Life > 0.0f){

            glDisable(GL_CULL_FACE);
            
            glm::mat4 projection = shader->getProjection();
            glm::mat4 view = shader->getView();
            
            update_model_matrix(particle.Position, particle.grados, glm::vec3(0,0,1), glm::vec3(particle.Scale,particle.Scale,1));
            
            glm::mat4 MVP = projection*view*ModelMatrix;      

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            /*Paso de valores al shader*/
            glUniformMatrix4fv(glGetUniformLocation(Shader::Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniform4fv(glGetUniformLocation(Shader::Program, "color"), 1, glm::value_ptr(particle.Color));
            glUniform1i(glGetUniformLocation(Shader::Program, "sprite"), 0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ID);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glEnable(GL_CULL_FACE);

        }
    }

    glDepthMask(true);
}

/* Actualiza posicion, la rotacion y escalado de las particulas */
void ParticleGenerator::update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado){
    glm::mat4 _rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(grados), rotation);
    glm::mat4 _escalado = glm::scale(escalado);
    glm::mat4 _traslacion = glm::translate(position);
  
    ModelMatrix =  _traslacion * _rotacion * _escalado;

    /* Obtener la matriz view para saber la rotacion que debe ponerse sobre la imagen */
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
    unsigned char *data = SOIL_load_image("Particulas/Polvo3.png", &width, &height, 0, SOIL_LOAD_RGBA);
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


    // Create this->amount default particle instances
    for (GLuint i = 0; i < this->amount; ++i)

        this->particles.push_back(Particle( glm::vec3(61.5158, 12, 44.2914), glm::vec3(0,1,0) * 0.1f, 0));
}

// Indice de la ultima particula usada
GLuint lastUsedParticle = 0;
/* Metodo si requiere crear una particula en ese preciso instante*/
GLuint ParticleGenerator::firstUnusedParticle()
{
    // Busca a partir de la ultima particula que fue previamente usada
    for (GLuint i = lastUsedParticle; i < amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Busqueda desde el inicio
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Ultima particula pasa a ser la primera
    lastUsedParticle = 0;
    return 0;
}

/*Metodo que no borra las particulas que estan en uso */
GLuint ParticleGenerator::firstUnusedParticle_Active()
{
    // Busca a partir de la ultima particula que fue previamente usada
    for (GLuint i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Busqueda desde el inicio
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }

    //Devuelve que no se puede crear ninguna
    return -1;
}

/* Se asignan los parametros que se envian para la particula que se esta reusando */
void ParticleGenerator::respawnParticle(Particle &particle, GLint _direccion, GLfloat scale_factor, glm::vec3 velocidad, glm::vec3 offset, GLfloat _i_duracion, GLfloat red, GLfloat green, GLfloat blue){
   
    GLfloat desp_x, desp_z;

	desp_z = cos((_direccion*std::acos(-1)/180));
    desp_x = sin((_direccion*std::acos(-1)/180));
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    GLfloat offposition = -0.5 + ((rand() % 100) / 100.0f);

    particle.Scale = 1 + (rand() % 2);
    particle.Scale_Factor = scale_factor;
    particle.Position = glm::vec3(offset.x + offposition, offset.y + offposition, offset.z + offposition);

    particle.Color = glm::vec4(red, green, blue, .9f);
    particle.Life = _i_duracion;
    particle.Velocity.x = -desp_x * velocidad.x;
    particle.Velocity.y = velocidad.y;
    particle.Velocity.z = -desp_z * velocidad.z;

}
 
