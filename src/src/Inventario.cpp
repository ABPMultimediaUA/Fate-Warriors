
/*Ojo cuidado con los core dumpeds, si se elimina el objeto sin decirle al _seleccionado que ese objeto se ha eliminado al intentar usarlo dara core dumped */
#include <iostream>
#include "Inventario.h"
#include "Armas/Arma_distancia.h"
#include "Armas/Arma_cerca.h"
#include "Llave.h"

Inventario::Inventario() : _objeto_cerca(nullptr), _objeto_distancia(nullptr), _seleccionado(nullptr){
	_arma=cuerpo_a_cuerpo;
}

Inventario::~Inventario(){

}

void Inventario::render(){

}

bool Inventario::usar(){
	bool salida = _seleccionado->usar(15,15,15);
	return salida;
}

/*Metodos SET*/
void Inventario::cambiar_objeto_cerca(Arma_cerca *_i_cerca){
/*	if(_objeto_cerca!=nullptr){
		//_objeto_cerca->set_borrar_true();
		_objeto_cerca = nullptr;
	}*/

	_objeto_cerca = _i_cerca;
	_seleccionado = _objeto_cerca;
}

void Inventario::cambiar_objeto_distancia (Arma_distancia *_i_distancia){
	/*	if(_objeto_distancia!=nullptr){
		//_objeto_distancia->set_borrar_true();
		_objeto_distancia = nullptr;
	}*/

	_objeto_distancia = _i_distancia;
	_seleccionado = _objeto_distancia;
}

void Inventario::cambiar_seleccionado(){

	if (_seleccionado == _objeto_cerca){
		_seleccionado = _objeto_distancia;
	}
	else {
		_seleccionado = _objeto_cerca;
	}

	std::cout << _objeto_distancia << std::endl;
	std::cout << _objeto_cerca << std::endl;

}

/*Metodos GET*/
Objeto* Inventario::get_seleccionado(){
	return _seleccionado;
}


Arma_cerca* Inventario::get_objeto_cerca(){
	return _objeto_cerca;
}


Arma_distancia* Inventario::get_objeto_distancia(){
	return _objeto_distancia;
}

std::vector<Llave*> Inventario::get_llaves(){
    return _llaves;
}

void Inventario::anadir_llave(Llave* _i_llave){
    _llaves.push_back(_i_llave);
}

void Inventario::eliminar_llave(Llave* _i_llave){
	bool encontrado = false;

	for(short _cont = 0; _cont < _llaves.size() && encontrado == false; _cont++) {

		if(_llaves[_cont]->get_id() == _i_llave->get_id()){
			_llaves.erase (_llaves.begin()+_cont);
			encontrado = true;
		}
	}
}

// CUerpo a cuerpo  = 1
// Distancia 		= 2
// Cerca			= 3

// Funciones para guardar los datos
struct MapeadoArmas{			// Declaracion de los parametros
	arma_Actual _nombre_objeto;
	void (Inventario::*pmet)();
};

MapeadoArmas mapping_armas_siguiente[] = {	// Definicion de los parametros
		{cuerpo_a_cuerpo, &Inventario::seleccionar_arma_distancia},
		{distancia, &Inventario::seleccionar_arma_cerca},
		{cerca, &Inventario::seleccionar_cuerpo_a_cuerpo}
};

MapeadoArmas mapping_armas_anterior[] = {	// Definicion de los parametros
		{cuerpo_a_cuerpo, &Inventario::seleccionar_arma_cerca},
		{distancia, &Inventario::seleccionar_cuerpo_a_cuerpo},
		{cerca, &Inventario::seleccionar_arma_distancia}
};


void Inventario::cambiar_arma_seleccionada_a_la_siguiente(){
	
	MapeadoArmas *_mapeado_clase = mapping_armas_siguiente;

	while(_mapeado_clase->_nombre_objeto){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;
	}
}

void Inventario::cambiar_arma_seleccionada_a_la_anterior(){
	
	MapeadoArmas *_mapeado_clase = mapping_armas_anterior;

	while(_mapeado_clase->_nombre_objeto){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;
	}
}

void Inventario::seleccionar_arma_distancia(){
	_seleccionado = _objeto_distancia;
	_arma = distancia;
}

void Inventario::seleccionar_arma_cerca(){
	_seleccionado = _objeto_cerca;
	_arma = cerca;
}

void Inventario::seleccionar_cuerpo_a_cuerpo(){
	_seleccionado = nullptr;
	_arma = cuerpo_a_cuerpo;
}
