#include "Puerta.h"
#include "Interfaz/Motor.h"
#include "Utilidades/Modelados.h"
#include "Nivel/Nivel.h"
//#include "Interfaz/Objeto_Motor.h"
#include <string>
Puerta::Puerta(short _i_id, float _i_x, float _i_y, float _i_z, bool _i_abierta) : Objeto(_i_id, _i_x, _i_y, _i_z), _abierta(_i_abierta) {
    
    const char* cstr  = "models/Interactuables/Puerta/Puerta.obj";

   // _id_motor = _motor->crear_objeto(E_BoundingBox, cstr, _i_x, _i_y, _i_z, 9999999);
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
}

void Puerta::set_abierta(bool _i_abierta){
	_abierta = _i_abierta;
    _objeto_motor->abrir_puerta();
    Nivel::nivel_instancia()->nivel_abrir_pasillo(8);
}

bool Puerta::get_abierta(){
    return _abierta;
}

Puerta::~Puerta() {
}
