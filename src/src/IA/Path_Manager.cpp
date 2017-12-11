#include "Path_Manager.h"

#include "Interfaz_Datos.h"

#include "../Interfaz_Libs/Lib_Math.h"

#include<iostream>

Path_Manager::Path_Manager(Interfaz_Datos& _i_interfaz_decision) {
	_interfaz_decision = &_i_interfaz_decision;

}

Path_Manager::~Path_Manager() {

}


unsigned short Path_Manager::get_direccion_movimiento(unsigned short _i_n_enemigo) {
	unsigned short _direccion;
	float _x_enemigo, _y_enemigo, _x_player, _y_player;

	_interfaz_decision->get_pos_player(_x_player, _y_player);
	_interfaz_decision->get_pos_enemigo(_i_n_enemigo, _x_enemigo, _y_enemigo);

	_direccion = lib_math_angulo_2_puntos( _x_player, _y_player, _x_enemigo, _y_enemigo);

	return _direccion;
}
