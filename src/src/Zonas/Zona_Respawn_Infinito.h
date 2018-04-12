#ifndef ZONA_RESPAWN_INFINITO_H_
#define ZONA_RESPAWN_INFINITO_H_

#include "Zona.h"

#include "../Objeto.h"
#include "../Personajes/Enum_Tipo_Ataque.h"

#include <vector>

class Character;
class Time;
class Interruptor;
class Player;

class Zona_Respawn_Infinito : public Zona{
public:
	Zona_Respawn_Infinito(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos, float _i_distancia);
    ~Zona_Respawn_Infinito();
    void actualizar_zona() override;

private:
    float _distancia_reaparecer;
    uint16_t _num_enemigos;
    void comprobar_si_reaparecer_npcs();
  
};

#endif /* ZONA_RESPAWN_INFINITO_H_ */