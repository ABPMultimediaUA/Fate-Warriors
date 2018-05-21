 

#include "Interfaz_Particulas.h"
#include "SOIL.h"
#include "Shader.h"
#include "glm/ext.hpp"
#include <iostream>
#include "ParticleGenerator.h"
#include "TMooseEngine.h"


Interfaz_Particulas::Interfaz_Particulas(){
   TMooseEngine* engine =  TMooseEngine::get_instancia();
   _particulas =  engine->get_gestor_particulas();
}


Interfaz_Particulas::~Interfaz_Particulas(){
    _particulas = nullptr;
}


void Interfaz_Particulas::Update(float dt){
    _particulas->Update(dt/1000);
}

void Interfaz_Particulas::Crear_particulas(float pos_x, float pos_y, float pos_z, uint16_t _direccion){
   _particulas->Reuse_Particles(1, glm::vec3(pos_x, pos_y, pos_z), _direccion);
}

void Interfaz_Particulas::Crear_particulas_Suelo(float pos_x, float pos_y, float pos_z, uint16_t _direccion){
   _particulas->Reuse_Particles_Ground(1, glm::vec3(pos_x, pos_y, pos_z), _direccion);
}