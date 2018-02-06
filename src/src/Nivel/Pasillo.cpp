

#include "Pasillo.h"
#include "Nodo_blackboard.h"

Pasillo::Pasillo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo): 
Vertice( _i_x, _i_y, _i_ancho, _i_alto, _i_id, _i_grafo){
	_blackboard = new Nodo_blackboard(_i_id,2);//maximo de 2 npc por pasillo
	_tipo_vertice=Vertice_Pasillo;
	//JINX WAS HERE!!
}

Pasillo::~Pasillo() {
	delete _blackboard;
}
