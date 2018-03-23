
#include <iostream>
#include "Inventario.h"
#include "Armas/Arma_distancia.h"
#include "Armas/Arma_cerca.h"
#include "Armas/Armas_Manager.h"
#include "Datos_Partida.h"
#include "Game.h"

#include "Llave.h"

Inventario::Inventario() : _objeto_cerca(nullptr), _objeto_distancia(nullptr), _seleccionado(nullptr){
	_arma = Tipo_Arma_cuerpo_a_cuerpo;
}

Inventario::~Inventario(){

}

void Inventario::render(){

}

void Inventario::crear_un_arma_al_azar_asignar_y_equipar(Armas_Manager* _armas_manager){
  _seleccionado = _armas_manager->anyadir_arma();
  _seleccionado->set_ocupada(true);

  //_seleccionado->setPositionXZ(999999,999999);

  
  if (dynamic_cast<Arma_cerca*>(_seleccionado) == NULL){
	 _objeto_distancia = (Arma_distancia*)_seleccionado;
    _arma = Tipo_Arma_distancia;
  }
  else{
	 _objeto_cerca = (Arma_cerca*)_seleccionado;
	 //  _objeto_cerca=dynamic_cast<Arma_cerca*>(_seleccionado);

    _arma = Tipo_Arma_cerca;
  }
  
}

void Inventario::soltar_armas(float x, float z){ 

  if(_objeto_distancia!=nullptr){
    _objeto_distancia->setPositionXZ(x,z); 
	_objeto_distancia->set_ocupada(false);
    _objeto_distancia = nullptr; 
  } 

  if(_objeto_cerca!=nullptr){ 
   _objeto_cerca->setPositionXZ(x,z); 
	_objeto_cerca->set_ocupada(false);
    _objeto_cerca = nullptr; 
  } 
  
  if(_seleccionado != nullptr){
	  _seleccionado->setPositionXZ(x,z); 
  }

  	_seleccionado = nullptr;
    _arma = Tipo_Arma_cuerpo_a_cuerpo;

} 




Character* Inventario::usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion){ 
	Character* personaje = _seleccionado->usar(_i_objeto_origen,_i_direccion);
	if(borrar_si_se_puede(_seleccionado) == true)
		return 0;
	return personaje;
}

bool Inventario::borrar_si_se_puede(Arma * seleccionado_in){

	if(seleccionado_in->get_uses()==0){
		Armas_Manager* _armas_manager = Game::game_instancia()->game_get_datos()->get_armas_manager();
		_armas_manager->borrar_arma(seleccionado_in);

		if(_arma == Tipo_Arma_distancia){
			_objeto_distancia = nullptr;
		}

		if(_arma == Tipo_Arma_cerca){
			_objeto_cerca = nullptr;
		}

		_armas_manager->crear_todas_las_armas_que_faltan();
		cambiar_arma_seleccionada_a_la_siguiente();

		return true;

	}
	return false;
}

/*Metodos SET*/
void Inventario::cambiar_objeto_cerca(Arma_cerca *_i_cerca){
	
	if(_i_cerca->get_ocupada()==false){

		Armas_Manager* _armas_manager = Game::game_instancia()->game_get_datos()->get_armas_manager();
		if(_objeto_cerca!=nullptr){
			//_objeto_cerca->set_borrar_true();
			_armas_manager->borrar_arma(_objeto_cerca);
		}
			_armas_manager->crear_todas_las_armas_que_faltan();

		_objeto_cerca = _i_cerca;
		_seleccionado = _objeto_cerca;
		_seleccionado->set_ocupada(true);
		
	}
}

void Inventario::cambiar_objeto_distancia (Arma_distancia *_i_distancia){
	if(_i_distancia->get_ocupada()==false){
			Armas_Manager* _armas_manager = Game::game_instancia()->game_get_datos()->get_armas_manager();
		if(_objeto_distancia!=nullptr){
			_armas_manager->borrar_arma(_objeto_distancia);

		}

		_armas_manager->crear_todas_las_armas_que_faltan();

		_objeto_distancia = _i_distancia;
		_seleccionado = _objeto_distancia;
		_seleccionado->set_ocupada(true);

	}
	
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
	//std::cout << "valor arma SIGUIENTE " << _arma;
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
	//std::cout << "Ahora tengo arma distancia\n";
	return Tipo_Arma_distancia;
}

enum Tipo_Arma Inventario::seleccionar_arma_cerca(){
	_seleccionado = _objeto_cerca;
	//std::cout << "Ahora tengo arma cerca\n";
	return Tipo_Arma_cerca;
}

enum Tipo_Arma Inventario::seleccionar_cuerpo_a_cuerpo(){
	_seleccionado = nullptr;
	//std::cout << "Ahora cuerpo a cuerpo\n";
	return Tipo_Arma_cuerpo_a_cuerpo;
}

void Inventario::seleccionar_arma_distancia_NPC(){
	_seleccionado = _objeto_distancia;
	//std::cout << "Ahora tengo arma distancia\n";
	_arma = Tipo_Arma_distancia;
}

void Inventario::seleccionar_arma_cerca_NPC(){
	_seleccionado = _objeto_cerca;
	_arma = Tipo_Arma_cerca;
	//std::cout << "Ahora tengo arma cerca\n";
}


enum Tipo_Arma Inventario::get_tipo_arma(){
	return _arma;
}

Enum_Nombre_Arma Inventario::get_nombre_arma(){
	if(_seleccionado==nullptr){
		return Nombre_Arma_Nada;
	}
	return _seleccionado->get_nombre();
}