#include "Puerta_Pincho.h"

#include "../Interfaz/Objeto_Motor.h"
#include "../Moose_Engine/src/iObjeto_Mapa.h"

#include "../Datos_Partida.h"
#include "../Game.h"
#include "../Nivel/Nivel.h"
#include "../Interfaz/Motor.h"
#include "../Personajes/Character.h"


Puerta_Pincho::Puerta_Pincho(short id, float _i_x, float _i_y,float _i_z, bool activada, float _i_rotacion, uint8_t _i_pasillo_asociado) : Objeto(id, _i_x, _i_y, _i_z){
    _pasillo_asociado = _i_pasillo_asociado;

    const char* cstr  = "pinchos_puerta_pinchos";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _objeto_motor->rotar_nodo(_i_rotacion);

    const char* cstr_2  = "base_puerta_pinchos";
    _basecita = new Objeto_Motor(this,E_BoundingBox, cstr_2, _i_x,_i_y,_i_z,0);
    _basecita->rotar_nodo(_i_rotacion);

    _objeto_visual_mapa = new iObjeto_Mapa(_i_x, _i_z, 50,25, Enum_Puerta_Pincho);

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
    if (_objeto_visual_mapa !=nullptr){
        eliminar_del_minimapa();
    }
}

void Puerta_Pincho::cambiar_icono_minimapa(float ancho, float alto, Texture_ID_Map _tipo){
    eliminar_del_minimapa();
    _objeto_visual_mapa = new iObjeto_Mapa(getX(), getZ(), ancho,alto, _tipo);
}


void Puerta_Pincho::activar() {
    if(!_bloqueado) {
        _activado = true;
        setY(6);
        Nivel::nivel_instancia()->nivel_cerrar_pasillo(_pasillo_asociado);
        cambiar_icono_minimapa(35, 15, Enum_Puerta_Pincho);
    }
}

void Puerta_Pincho::desactivar() {
    if(!_bloqueado) {
        _activado = false;   
        setY(-5.95);
        eliminar_del_minimapa();
    }
}

void Puerta_Pincho::desactivar_bloquear() {
    if(!_bloqueado) {
        _activado = false;   
        setY(-5.95);
        Nivel::nivel_instancia()->nivel_abrir_pasillo(_pasillo_asociado);
        eliminar_del_minimapa();
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

void Puerta_Pincho::eliminar_del_minimapa(){
    delete _objeto_visual_mapa;
    _objeto_visual_mapa = nullptr;
}