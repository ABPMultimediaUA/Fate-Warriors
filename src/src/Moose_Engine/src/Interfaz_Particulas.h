 
#ifndef INTERFAZ_PARTICULAS_H
#define INTERFAZ_PARTICULAS_H

#include <cstdint>

class Shader;
class ParticleGenerator;


class Interfaz_Particulas{

public:

    // Constructor
    Interfaz_Particulas();
    ~Interfaz_Particulas();

    // Update all particles
    void Update(float dt);

    //Crea las particulas para que se muevan en una direccion
    void Crear_particulas(float pos_x, float pos_y, float pos_z, uint16_t _direccion);


private:
    ParticleGenerator* _particulas;
};

#endif 