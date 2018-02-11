#include "Zona.h"
#include "Interfaz/Motor.h"

Zona::Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo){

    _equipo = i_equipo;
    _rb = Motor::Motor_GetInstance()->crear_rb_ataque();
    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb,btVector3(_i_x,_i_y,_i_z), btVector3(long_x,10,long_y), 0);
}

Zona::~Zona() {
    Motor::Motor_GetInstance()->borrar_rb(_rb);
}
