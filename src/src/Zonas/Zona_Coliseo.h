#ifndef ZONA_COLISEO_H_
#define ZONA_COLISEO_H_

#include "Zona.h"

#include "../Objeto.h"
#include "../Personajes/Enum_Tipo_Ataque.h"

#include <vector>

class Character;
class Time;
class Interruptor;
class Player;

class Zona_Coliseo : public Zona{
public:
	Zona_Coliseo(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos,  int rondas);
    ~Zona_Coliseo();
    void actualizar_zona() override;

private:
    void iniciar_coliseo();
    void update_coliseo();
    bool _coliseo_iniciado;
    uint16_t _num_enemigos;
    int _rondas;
};

#endif /* ZONA_COLISEO_H_ */