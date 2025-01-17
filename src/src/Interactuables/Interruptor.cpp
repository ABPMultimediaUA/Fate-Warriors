#include "Interruptor.h"

#include "Puerta_Pincho.h"

#include "../Game.h"
#include "../Tiempo/Time.h"
#include "../Motor_sonido/Interfaz_sonido.h"
#include "../Moose_Engine/src/iObjeto_Mapa.h"


#include <iostream>

Interruptor::Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion, short _i_rotacion_x, short _i_rotacion_y, short _i_distancia) : Objeto(_i_id, _i_x, 0, _i_z){ 
    _inclinacion_palito = 35;

    const char* cstr  = "BaseInterruptor";
    _objeto_motor = new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,0,_i_z,0);
    _objeto_motor->rotar_nodo(_i_rotacion);

    const char* cstr_2  = "PalancaInterruptor";
	_palito = new Objeto_Motor(this, E_BoundingBox, cstr_2, _i_x, -1.8, _i_z, 0, _inclinacion_palito);
    _palito->rotar_nodo(_i_rotacion);

    _estado = false;

	_reloj = Time::Instance();

    _rotacion_x = _i_rotacion_x;
    _rotacion_y = _i_rotacion_y;
    _distancia = _i_distancia;
    _objeto_visual_mapa = new iObjeto_Mapa(_i_x, _i_z, 25,25, Enum_Interruptor);


    _sonido = Interfaz_sonido::GetInstancia();
}

Interruptor::~Interruptor() {
	delete _palito;

    _puertas_asociadas.clear();

    if (_objeto_visual_mapa !=nullptr){
        eliminar_del_minimapa();
    }

}


void Interruptor::accionar_sin_propagar() {
    accionar();
}

void Interruptor::agregar_puerta(Puerta_Pincho* _puerta) {
    _puertas_asociadas.push_back(_puerta);
}

void Interruptor::agregar_interruptor(Interruptor* _interruptor) {
}


void Interruptor::update(){
}

void Interruptor::iniciar_interruptor(){
    if(!_estado) {
        _sonido->Play_escenario(6);
	    Game::game_instancia()->cambio_a_update_mirar(Time::Instance()->get_current() + 4000, this, 90, 30, 20);
    }
}

Puerta_Pincho* Interruptor::get_puerta_asociada(){
    return _puertas_asociadas[0];
}


void Interruptor::cambia_palito() {
    if(_inclinacion_palito == 35)
        _inclinacion_palito = 325;
    else
        _inclinacion_palito = 35;

    _palito->rota_palanca(_inclinacion_palito);

    _sonido->Play_escenario(5);
}


short Interruptor::get_rotacion_x(){
    return _rotacion_x;
}


short Interruptor::get_rotacion_y(){
    return _rotacion_y;
}

short Interruptor::get_distancia(){
    return _distancia;
}

void Interruptor::eliminar_del_minimapa(){
    delete _objeto_visual_mapa;
    _objeto_visual_mapa = nullptr;
}

void Interruptor::cambiar_icono_ascociados(Texture_ID_Map textura) {
    uint8_t size = _puertas_asociadas.size();

    for(uint8_t i=0; i<size; i++) {
    	_puertas_asociadas[i]->cambiar_icono_minimapa(25,25,textura);
    }
    
}