#include "Path_Manager.h"

#include "Interfaz_Datos.h"

#include "../Nivel/Nivel.h"

#include<iostream>

Path_Manager::Path_Manager(Interfaz_Datos& _i_interfaz_decision) {
	_interfaz_decision = &_i_interfaz_decision;

}

Path_Manager::~Path_Manager() {

}


unsigned short Path_Manager::get_direccion_movimiento(unsigned short _i_n_enemigo) {
	unsigned short _direccion;
	float _x_enemigo, _y_enemigo, _x_player, _y_player;
	Nivel* nivel=Nivel::nivel_instancia();
	_interfaz_decision->get_pos_player(_x_player, _y_player);
	_interfaz_decision->get_pos_enemigo(_i_n_enemigo, _x_enemigo, _y_enemigo);

	_direccion = nivel->nivel_pathfindinglod1( _x_player, _y_player, _x_enemigo, _y_enemigo);

	return _direccion;
}
