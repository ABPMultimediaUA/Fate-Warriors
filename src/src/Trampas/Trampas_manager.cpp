#include "Trampas_manager.h"
#include "../Tiempo/Time.h"
#include "Pinchos.h"
#include "Minas.h"
#include "Charcos_electrificados.h"

// CONSTRUCTOR

Trampas_manager::Trampas_manager() {
	_n_minas = 3;
	_minas	 = new Minas*[_n_minas];
	for(unsigned short _cont=0; _cont<_n_minas; _cont++) {
		//_minas[_cont] = new Minas(6,25,56,0);
	}
		_minas[0] = new Minas(6,25,56,0);
			_minas[1] = new Minas(6,120,56,56);
				_minas[2] = new Minas(6,96,56,0);

	_n_charcos = 3;
	_charcos = new Charcos_electrificados*[_n_minas];

	for(unsigned short _cont=0; _cont<_n_charcos; _cont++) {
		_charcos[_cont] = new Charcos_electrificados(0,19,0,0);
	}

    _n_pinchos = 3;
	_pinchos = new Pinchos*[_n_pinchos];

	for(unsigned short _cont=0; _cont<_n_pinchos; _cont++) {
		_pinchos[_cont] = new Pinchos(0,19,0,0);
	}						
}

// DESTRUCTOR

Trampas_manager::~Trampas_manager(){

	for(unsigned short _cont=0; _cont<_n_minas; _cont++) {
		delete _minas[_cont];
	}
	delete [] _minas;


	for(unsigned short _cont=0; _cont<_n_charcos; _cont++) {
		delete _charcos[_cont];
	}
	delete [] _charcos;
	
	for(unsigned short _cont=0; _cont<_n_pinchos; _cont++) {
		delete _pinchos[_cont];
	}
	delete [] _pinchos;
}


// METODOS BORRAR

void Trampas_manager::borrar_mina(){
	short _n_minas_aux = _n_minas;

	for(short i=0; i<_n_minas_aux; i++){
		if(_minas[i]->explota()){
			delete _minas[i];
			for(short a=i; a<_n_minas-1; a++){
				_minas[a]=_minas[a+1];
			}
			_n_minas--;
		}
	}
}


/// METODOS GET 


unsigned short Trampas_manager::get_n_trampas_mina(){
    return _n_minas;
}

unsigned short Trampas_manager::get_n_trampas_charco(){
    return _n_charcos;
}

unsigned short Trampas_manager::get_n_trampas_pincho(){
    return _n_pinchos;
}

Minas** Trampas_manager::get_trampas_mina(){
    return _minas;
}

Pinchos** Trampas_manager::get_trampas_pinchos(){
    return _pinchos;
}

Charcos_electrificados** Trampas_manager::get_trampas_charco(){
    return _charcos;
}
