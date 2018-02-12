#include "Armas_Manager.h"
#include "../Tiempo/Time.h"
#include "Arma.h"
#include "Proyectil.h"

 #include "AD_Ametralladora.h"
 #include "AC_Katana.h"
 #include "AD_Pistola.h"


// CONSTRUCTOR

Armas_Manager::Armas_Manager() {
    
    float mult = 4.9212625;
	_armas.push_back(new AD_Ametralladora(5,mult*18, mult*0, mult*15));
    
    _armas.push_back(new AC_Katana(5,mult*10, mult*0, mult*10));
}

// DESTRUCTOR

Armas_Manager::~Armas_Manager(){
    
 for (short i = 0; i < _armas.size(); i++) {
    delete _armas[i];
  }
  _armas.clear();
  
}


// METODOS BORRAR

void Armas_Manager::borrar_arma(Arma* objeto){

    std::vector<Arma*>::iterator it;
    it = std::find(_armas.begin(), _armas.end(), objeto);
    if ( it != _armas.end()){
        _armas.erase(it);
        delete objeto;
    }
   
}

void Armas_Manager::anyadir_proyectil(Proyectil* _i_bala){
    _balas.push_back(_i_bala);
}

void Armas_Manager::borrar_proyectil(Proyectil* objeto){

    std::vector<Proyectil*>::iterator it;
    it = std::find(_balas.begin(), _balas.end(), objeto);
    if ( it != _balas.end()){
        _balas.erase(it);
        delete objeto;
    }
}

void Armas_Manager::borrar_arma(short id){
    delete _armas[id];
    _armas.erase(_armas.begin() + id);
}

void Armas_Manager::crear_ametralladora(Vector2 posicion){
	_armas.push_back(new AD_Ametralladora(5, posicion._x, 0, posicion._y));
}

void Armas_Manager::crear_pistola(Vector2 posicion){
	_armas.push_back(new AD_Pistola(5, posicion._x, 0, posicion._y));
}
void Armas_Manager::crear_katana(Vector2 posicion){
	_armas.push_back(new AC_Katana(5, posicion._x, 0, posicion._y));
}
/*
void Armas_Manager::crear_ametralladora(Vector2 posicion){
	_armas.push_back(new AD_Ametralladora(5, posicion._x, 0, posicion._y));
}
*/
/// METODOS GET 

std::vector<Arma*>* Armas_Manager::get_armas(){
    return &_armas;
}

