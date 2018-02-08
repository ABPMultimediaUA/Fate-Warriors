#include "Path_Manager.h"

#include "Interfaz_Datos.h"

#include "../Nivel/Nivel.h"

#include<iostream>

Path_Manager::Path_Manager(Interfaz_Datos& _i_interfaz_decision) {
	_interfaz_decision = &_i_interfaz_decision;

}

Path_Manager::~Path_Manager() {

}


uint16_t Path_Manager::get_direccion_movimiento(float& _x_enemigo,float& _y_enemigo) {
	uint16_t _direccion;
	float  _x_player, _y_player;
	Nivel* nivel=Nivel::nivel_instancia();
	_interfaz_decision->get_pos_player(_x_player, _y_player);

	_direccion = nivel->nivel_pathfinding(_x_enemigo,_y_enemigo,_x_player,_y_player);
	return _direccion;
}
