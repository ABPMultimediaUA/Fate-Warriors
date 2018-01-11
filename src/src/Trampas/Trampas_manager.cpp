#include "Trampas_manager.h"
#include "../Tiempo/Time.h"
#include "Pinchos.h"
#include "Minas.h"
#include "Charcos_electrificados.h"

// CONSTRUCTOR

Trampas_manager::Trampas_manager() {
  float mult = 4.9212625;

  _n_minas = 1;
  _minas   = new Minas*[_n_minas];
  _minas[0] = new Minas(6,15*mult, 0, 60*mult);
 
  /*for(unsigned short _cont=0; _cont<_n_minas; _cont++) {
    _minas[_cont] = new Minas(6,25,56,0);
  }*/
  
  //_minas[1] = new Minas(6,mult*25,0,mult*56);
  //_minas[2] = new Minas(6,mult*96,0,mult*0);
 
  _n_charcos = 1;
  _charcos = new Charcos_electrificados*[_n_charcos];
  _charcos[0] = new Charcos_electrificados(0,10*mult, 0, 60*mult);
 
  /*for(unsigned short _cont=0; _cont<_n_charcos; _cont++) {
    _charcos[_cont] = new Charcos_electrificados(0,mult*15,0,mult*15);
  }*/


  _n_pinchos = 0;
  _pinchos = new Pinchos*[_n_pinchos];
  _pinchos[0] = new Pinchos(0,5*mult, 0, 60*mult);
 
  /*for(unsigned short _cont=0; _cont<_n_pinchos; _cont++) {
    _pinchos[_cont] = new Pinchos(0,mult*15,0,mult*10);
  }*/    
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

	for(short i=0; i<_n_minas; i++){

		if(_minas[i]->explota()){
			_n_minas--;
			delete _minas[i];
			if(_n_minas>1)
			for(short a=i; a<_n_minas; a++){
				_minas[a]=_minas[a+1];
			}
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
