#ifndef ZONA_FINAL_H_
#define ZONA_FINAL_H_

#include "Zona.h"

#include "../Objeto.h"
#include "../Personajes/Enum_Tipo_Ataque.h"

#include <vector>

class Character;
class Time;
class Interruptor;

class Zona_Final : public Zona{
public:
	Zona_Final(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    ~Zona_Final();
    void actualizar_zona() override; 

};

#endif /* ZONA_FINAL_H_ */