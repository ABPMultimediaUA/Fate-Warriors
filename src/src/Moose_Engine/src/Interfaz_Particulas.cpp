

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

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
   // _particulas = ParticleGenerator::instancia();
}


Interfaz_Particulas::~Interfaz_Particulas(){
    _particulas = nullptr;
}


void Interfaz_Particulas::Update(float dt){
    _particulas->Update(dt/1000);
}

void Interfaz_Particulas::Crear_particulas(float pos_x, float pos_y, float pos_z, uint16_t _direccion){
   // _particulas->respawnParticle(float pos_x, float pos_y, float pos_z, uint16_t _direccion);
        GameObject obje =  GameObject();
   _particulas->Reuse_Particles(obje, 1, glm::vec2(pos_x, pos_z), _direccion);
}