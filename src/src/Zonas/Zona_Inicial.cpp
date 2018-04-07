#include "Zona_Inicial.h"

#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"
#include "../Personajes/Player.h"

Zona_Inicial::Zona_Inicial(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo) : Zona(_i_x, _i_y, _i_z, long_x, long_y, i_equipo){
    _x_inicial = _i_x;
    _y_inicial = _i_y;
}

Zona_Inicial::Zona_Inicial(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo, float _i_x_inicial, float _i_y_inicial) : Zona(_i_x, _i_y, _i_z, long_x, long_y, i_equipo){
    _x_inicial = _i_x_inicial;
    _y_inicial = _i_y_inicial;
}

Zona_Inicial::~Zona_Inicial() {

}


/*Metodo para actualizar los valores de la zona*/

void Zona_Inicial::actualizar_zona(){
   
}


Vector2 Zona_Inicial::get_posicion_inicial() {
    return Vector2(_x_inicial, _y_inicial);
}