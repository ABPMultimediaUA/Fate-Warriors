#include "Puerta_Pincho.h"
#include "Trampas/Pinchos.h"
#include "Tiempo/Time.h"
#include "Interfaz/Objeto_Motor.h"

Puerta_Pincho::Puerta_Pincho(short id, float _i_x, float _i_y,float _i_z, Zona* _i_asociada_1, Zona* _i_asociada_2){
    _zona_asociada1 = _i_asociada_1;
    _zona_asociada2 = _i_asociada_2;
    _reloj = Time::Instance();

    _pinchos = new Pinchos(0,_i_x, _i_y, _i_z);
    _activado = false;
}

Puerta_Pincho::~Puerta_Pincho() {
    delete _pinchos;
}

void Puerta_Pincho::activar(){
    _activado = true;
    _tiempo_restante = _reloj->get_current() + 5000;
    _pinchos->get_objeto_motor()->setPositionY(0);
}

void Puerta_Pincho::desactivar(){
    _activado = false;
    _pinchos->get_objeto_motor()->setPositionY(-20);
}

bool Puerta_Pincho::comprobar_si_finalizo_el_tiempo(){

    if(_reloj->get_current()>_tiempo_restante){
        return true;
    }
    return false;
}

bool Puerta_Pincho::get_activado(){
    return _activado;
}