
/*Ojo cuidado con los core dumpeds, si se elimina el objeto sin decirle al _seleccionado que ese objeto se ha eliminado al intentar usarlo dara core dumped */
#include <iostream>
#include "Inventario.h"
#include "Armas/Arma_distancia.h"
#include "Armas/Arma_cerca.h"

Inventario::Inventario() : _objeto_cerca(nullptr), _objeto_distancia(nullptr), _seleccionado(nullptr){

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
	if(_seleccionado!=nullptr && _objeto_cerca!=nullptr && _objeto_distancia!=nullptr){
		if (_seleccionado == _objeto_cerca){
			_seleccionado = _objeto_distancia;
		}
		else {
			_seleccionado = _objeto_cerca;
		}

		std::cout << _objeto_distancia << std::endl;
		std::cout << _objeto_cerca << std::endl;
	}
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
