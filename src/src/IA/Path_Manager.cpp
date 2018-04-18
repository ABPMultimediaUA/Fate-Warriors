#include "Path_Manager.h"

#include "Interfaz_Datos.h"

#include "../Nivel/Nivel.h"
#include "../Objeto.h"

#include<iostream>

Path_Manager::Path_Manager() {
}

Path_Manager::~Path_Manager() {

}

uint16_t Path_Manager::get_direccion_movimiento(float& _x_enemigo,float& _y_enemigo, float pos_x, float pos_y) {
	uint16_t _direccion;
	Nivel* nivel=Nivel::nivel_instancia();

	_direccion = nivel->nivel_pathfinding(_x_enemigo,_y_enemigo,pos_x,pos_y);
	return _direccion;
}
