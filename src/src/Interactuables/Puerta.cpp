#include "Puerta.h"

#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"
#include "../Nivel/Nivel.h"
#include "../Motor_sonido/Interfaz_sonido.h"
#include "../Moose_Engine/src/iObjeto_Mapa.h"


Puerta::Puerta(short _i_id, float _i_x, float _i_y, float _i_z, float _i_rotacion, bool _i_abierta, uint16_t _i_id_pasillo_que_abre) : Objeto(_i_id, _i_x, _i_y, _i_z), _id_pasillo_que_abre(_i_id_pasillo_que_abre),_abierta(_i_abierta) {
    
    const char* cstr  = "puerta";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    
    _abierta = false;
    Nivel::nivel_instancia()->nivel_cerrar_pasillo(_id_pasillo_que_abre);

    _objeto_visual_mapa = new iObjeto_Mapa(_i_x, _i_z, 18, 36, Enum_Puerta);

    _objeto_motor->rotar_nodo(_i_rotacion);
    _sonido= Interfaz_sonido::GetInstancia();

    if(_i_rotacion == 0) 
        _rotacion = 0;
    else if(_i_rotacion == 180)
        _rotacion = 1;
}

Puerta::~Puerta() {
    if (_objeto_visual_mapa !=nullptr){
        eliminar_del_minimapa();
    }
}

void Puerta::set_abierta(){
	_abierta = true;
    _sonido->Play_escenario(0);
    _objeto_motor->abrir_puerta(_rotacion);
    Nivel::nivel_instancia()->nivel_abrir_pasillo(_id_pasillo_que_abre);
}

bool Puerta::get_abierta(){
    return _abierta;
}

std::tuple<float, float> Puerta::get_posicion_cerrojo() {
    if(_rotacion == 0)
        return std::make_tuple(_objeto_motor->getX()+5.25, _objeto_motor->getZ()-6.25);
    else //if(_rotacion == 1)
        return std::make_tuple(_objeto_motor->getX()-5.25, _objeto_motor->getZ()+6.25);
}

float Puerta::get_rotacion_cerrojo() {
    if(_rotacion == 0) 
        return 0;
    else //if(_rotacion == 1)
        return 180;
}

void Puerta::eliminar_del_minimapa(){
    delete _objeto_visual_mapa;
    _objeto_visual_mapa = nullptr;
}