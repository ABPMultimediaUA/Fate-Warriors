#include "Inventario.h"

#include "../Datos_Partida.h"
#include "../Game.h"

#include "../Interactuables/Llave.h"

Inventario::Inventario(){
}

Inventario::~Inventario(){
}

void Inventario::render(){
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