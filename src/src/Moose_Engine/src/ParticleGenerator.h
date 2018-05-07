#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

class Shader;

// Represents a single particle and its state
struct Particle {
    glm::vec3 Position;
    glm::vec3 Velocity;
    glm::vec4 Color;
    GLfloat Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
    Particle(glm::vec3 _i_Position, glm::vec3 _i_Velocity, glm::vec4 _i_Color, GLfloat _i_Life) : Position(_i_Position), Velocity(_i_Velocity), Color(_i_Color), Life(_i_Life) { }
    Particle(glm::vec3 _i_Position, glm::vec3 _i_Velocity, GLfloat _i_Life) : Position(_i_Position), Velocity(_i_Velocity), Color(1.0f), Life(_i_Life) { }
};


// Represents a single particle and its state
struct GameObject {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;

    GameObject() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class ParticleGenerator
{
public:
    // Constructor
    ParticleGenerator(Shader* shader, const char* texture, GLuint amount);
    ~ParticleGenerator();

    // Update all particles
    void Update(GLfloat dt);
    // Render all particles
    void Draw();
    void Reuse_Particles(GameObject &object, GLuint newParticles, glm::vec2 offset, GLint _direccion);
private:
    // State
    std::vector<Particle> particles;
    GLuint amount;
    // Render state
    Shader* shader;
    const char* texture;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    void update_model_matrix(glm::vec3 position, float grados, glm::vec3 rotation, glm::vec3 escalado);

    // Initializes buffer and vertex attributes
    void init();
    // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    GLuint firstUnusedParticle();
    // Respawns particle
    void respawnParticle(Particle &particle, GLint _direccion, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    void load_texture();

    glm::mat4 _traslacion;
    glm::mat4 _rotacion;
    glm::mat4 _escalado;
    glm::mat4 ModelMatrix;
    

    GLuint ID;

};

#endif 
