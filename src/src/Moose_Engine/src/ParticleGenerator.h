#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;

// Representa una unica particula
struct Particle {
    glm::vec3 Position;
    glm::vec3 Velocity;
    glm::vec4 Color;
    GLfloat Life;
    GLfloat Scale;
    GLfloat Scale_Factor;
    GLint grados;

    Particle(glm::vec3 _i_Position, glm::vec3 _i_Velocity, GLfloat _i_Life) : Position(_i_Position), Velocity(_i_Velocity), Color(1.0f), Life(_i_Life), Scale(3.f), Scale_Factor(3.f), grados(3.f) { }
};


class ParticleGenerator
{
public:

    // Constructor
    ParticleGenerator(Shader* shader,  GLuint amount);
    ~ParticleGenerator();

    // Actualiza la posicion de la particula es llamado desde el bucle principal del juego
    void Update(GLfloat dt);
    // Dibuja las particulas 
    void Draw();
    // Particulas para la sangre
    void Reuse_Particles(GLuint newParticles, glm::vec3 offset, GLint _direccion);
    //Particulas para el suelo
    void Reuse_Particles_Ground(GLuint newParticles, glm::vec3 offset, GLint _direccion);

private:
    // State
    std::vector<Particle> particles;

    //Cantidad de particulas que hay en el juego
    GLuint amount;

    // Render state
    Shader* shader;

    //BUffers
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    //Se encarga de posicionar en el mundo las posiciones de las particulas
    void update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado);

    // Initializes buffer and vertex attributes
    void init();
    
    // Devuelve el indice de la primera particula que es usada Life <= 0.0f or 0 - si la particula no esta actualmente inactiva
    GLuint firstUnusedParticle();

    // Devuelve el indice de la primera particula que es usada Life <= 0.0f or 0
    GLuint firstUnusedParticle_Active();

    // Revive una particula
    void respawnParticle(Particle &particle, GLint _direccion, GLfloat scale_factor, glm::vec3 velocidad, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f), GLfloat _i_duracion = .75f,  GLfloat red = 1, GLfloat green = 0, GLfloat blue = 0);
    //Carga la textura
    void load_texture();

    glm::mat4 ModelMatrix;
    GLuint ID;

};

#endif 