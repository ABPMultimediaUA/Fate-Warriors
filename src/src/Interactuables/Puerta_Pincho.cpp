#include "Puerta_Pincho.h"

#include "../Interfaz/Objeto_Motor.h"
#include "../Datos_Partida.h"
#include "../Game.h"
#include "../Nivel/Nivel.h"
#include "../Interfaz/Motor.h"
#include "../Personajes/Character.h"

Puerta_Pincho::Puerta_Pincho(short id, float _i_x, float _i_y,float _i_z, bool activada, float _i_rotacion, uint8_t _i_pasillo_asociado) : Objeto(id, _i_x, _i_y, _i_z){
    _pasillo_asociado = _i_pasillo_asociado;

    const char* cstr  = "models/Interactuables/PuertaPinchos/Puerta/pinchos_puerta_pinchos.obj";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _objeto_motor->rotar_nodo(_i_rotacion);

    const char* cstr_2  = "models/Interactuables/PuertaPinchos/Base/base_puerta_pinchos.obj";
    _basecita = new Objeto_Motor(this,E_BoundingBox, cstr_2, _i_x,_i_y,_i_z,0);
    _basecita->rotar_nodo(_i_rotacion);

    if(activada){
        activar();
    }
    else{
        desactivar();
    }

    _bloqueado = false;
}

Puerta_Pincho::~Puerta_Pincho() {
    delete _basecita;
}

void Puerta_Pincho::activar() {
    if(!_bloqueado) {
        _activado = true;
        setY(6);
        Nivel::nivel_instancia()->nivel_cerrar_pasillo(_pasillo_asociado);
    }
}

void Puerta_Pincho::desactivar() {
    if(!_bloqueado) {
        _activado = false;   
        setY(-5.95);
        Nivel::nivel_instancia()->nivel_abrir_pasillo(_pasillo_asociado);
    }
}

void Puerta_Pincho::desactivar_bloquear() {
    if(!_bloqueado) {
        _activado = false;   
        setY(-5.95);
        Nivel::nivel_instancia()->nivel_abrir_pasillo(_pasillo_asociado);

        _bloqueado = true;
    }
}

void Puerta_Pincho::cambiar_estado() {
    if(!_activado) {
        activar();
    }
    else {
        desactivar();
    }
}