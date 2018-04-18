#include "Trampas.h"

#include "../Tiempo/Time.h"
#include "../Interfaz/Motor.h"


Trampas::Trampas(short _id, float _i_x, float _i_y,float _i_z, short _i_danyo) : Objeto(_id, _i_x, _i_y,  _i_z),
                                                                                _danyo(_i_danyo),
                                                                                _reloj(Time::Instance())
{}

Trampas::~Trampas() {
}


void Trampas::activar(){
    _activa = true;
}

void Trampas::desactivar(){
    _activa = false;
 }

 bool Trampas::get_estado(){
     return _activa;
 }

 short Trampas::get_danyo(){
     return _danyo;
 }