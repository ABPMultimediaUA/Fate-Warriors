#ifndef ZONA_H_
#define ZONA_H_

#include "Objeto.h"
#include "Personajes/Enum_Tipo_Ataque.h"

class Zona{
public:
	Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo equipo);
    ~Zona();

    //void actualizar_characters();
    //Character ** get_characters();
    //int get_num_characters();

private:
    btRigidBody *_rb;
    Enum_Equipo _equipo;
    //Character ** _characters;
    //int _num_characters;
};

#endif /* ZONA_H_ */