#include "Armas_Manager.h"
#include "../Tiempo/Time.h"
#include "Arma.h"

 #include "AD_Ametralladora.h"


// CONSTRUCTOR

Armas_Manager::Armas_Manager() {
    
    float mult = 4.9212625;
	_armas.push_back(new AD_Ametralladora(5,mult*18, mult*0, mult*15));
}

// DESTRUCTOR

Armas_Manager::~Armas_Manager(){
    
 for (short i = 0; i < _armas.size(); ++i) {
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

void Armas_Manager::borrar_arma(short id){
    delete _armas[id];
    _armas.erase(_armas.begin() + id);
}



/// METODOS GET 

std::vector<Arma*>* Armas_Manager::get_armas(){
    return &_armas;
}

