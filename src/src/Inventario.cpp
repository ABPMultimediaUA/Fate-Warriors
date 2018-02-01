
/*Ojo cuidado con los core dumpeds, si se elimina el objeto sin decirle al _seleccionado que ese objeto se ha eliminado al intentar usarlo dara core dumped */
#include <iostream>
#include "Inventario.h"
#include "Armas/Arma_distancia.h"
#include "Armas/Arma_cerca.h"
#include "Llave.h"

Inventario::Inventario() : _objeto_cerca(nullptr), _objeto_distancia(nullptr), _seleccionado(nullptr){
	_arma = Tipo_Arma_cuerpo_a_cuerpo;
}

Inventario::~Inventario(){

}

void Inventario::render(){

}

Character* Inventario::usar(uint16_t _i_direccion){
	return _seleccionado->usar(_i_direccion);
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
	Tipo_Arma _nombre_objeto;
	enum Tipo_Arma (Inventario::*pmet)();
};

MapeadoArmas mapping_armas_siguiente[] = {	// Definicion de los parametros
		{Tipo_Arma_cuerpo_a_cuerpo, &Inventario::seleccionar_arma_distancia},
		{Tipo_Arma_distancia, &Inventario::seleccionar_arma_cerca},
		{Tipo_Arma_cerca, &Inventario::seleccionar_cuerpo_a_cuerpo}
};

MapeadoArmas mapping_armas_anterior[] = {	// Definicion de los parametros
		{Tipo_Arma_cuerpo_a_cuerpo, &Inventario::seleccionar_arma_cerca},
		{Tipo_Arma_distancia, &Inventario::seleccionar_cuerpo_a_cuerpo},
		{Tipo_Arma_cerca, &Inventario::seleccionar_arma_distancia}
};


void Inventario::cambiar_arma_seleccionada_a_la_siguiente(){
	enum Tipo_Arma _arma_aux;
	MapeadoArmas *_mapeado_clase = mapping_armas_siguiente;

	while(_mapeado_clase->_nombre_objeto){
		if(_arma == _mapeado_clase->_nombre_objeto){
			_arma_aux = (this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;
	}

	_arma = _arma_aux;
	if (_seleccionado==nullptr && _arma!=Tipo_Arma_cuerpo_a_cuerpo){
		cambiar_arma_seleccionada_a_la_siguiente();
	}
}

void Inventario::cambiar_arma_seleccionada_a_la_anterior(){
	enum Tipo_Arma _arma_aux;
	MapeadoArmas *_mapeado_clase = mapping_armas_anterior;

	while(_mapeado_clase->_nombre_objeto){
		if(_arma == _mapeado_clase->_nombre_objeto){
			_arma_aux = (this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;
	}

	_arma = _arma_aux;
	if (_seleccionado==nullptr && _arma!=Tipo_Arma_cuerpo_a_cuerpo){
		cambiar_arma_seleccionada_a_la_anterior();
	}
}

enum Tipo_Arma Inventario::seleccionar_arma_distancia(){
	_seleccionado = _objeto_distancia;
	std::cout << "Ahora tengo arma distancia\n";
	return Tipo_Arma_distancia;
}

enum Tipo_Arma Inventario::seleccionar_arma_cerca(){
	_seleccionado = _objeto_cerca;
	std::cout << "Ahora tengo arma cerca\n";
	return Tipo_Arma_cerca;
}

enum Tipo_Arma Inventario::seleccionar_cuerpo_a_cuerpo(){
	_seleccionado = nullptr;
	std::cout << "Ahora cuerpo a cuerpo\n";
	return Tipo_Arma_cuerpo_a_cuerpo;
}

enum Tipo_Arma Inventario::get_tipo_arma(){
	return _arma;
}
