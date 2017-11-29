#include "Arma_distancia.h"
#include "Bala.h"
#include <iostream>
//#include <list>

Arma_distancia::Arma_distancia(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses) : Arma(_id, _i_x, _i_y, _i_z,_i_ancho, _i_alto, _i_uses){
	std::cout << "Pistola" << std::endl;
	_cargadores = 3;
	_balas_totales =89;
	_balas_por_cargador=56;
	_uses = _balas_por_cargador;

}

Arma_distancia::~Arma_distancia(){
	
}

bool Arma_distancia::usar(){
	if (decrease_uses()){
		/*
		std::cout << Balas.size();
		Balas.push_back(Bala(15,15,15,15));
		*/

		return true;
	}
	
	else if(_cargadores>0){
		recargar_arma();
		return true;
	}

	return false;
}


void Arma_distancia::update(){
	/*for (std::list<Bala>::iterator itr = Balas.begin(); itr != Balas.end(); /*nothing*//*){
	    if (itr->get_state()==false)
	        itr = Balas.erase(itr);
	    else
	        ++itr;
	}
	*/
}


void Arma_distancia::render(){

}


void Arma_distancia::recargar_arma(){
	if(_cargadores>0){
		std::cout << "recargar_arma" << std::endl;
		if(_balas_totales>_balas_por_cargador){
			_uses = _balas_por_cargador;
		}
		else{
			_uses = _balas_totales;
		}
		_balas_totales-=_uses;
		_cargadores--;
	}
}