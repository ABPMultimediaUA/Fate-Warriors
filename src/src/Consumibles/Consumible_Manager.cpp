#include "Consumible_Manager.h"
#include "../Tiempo/Time.h"
#include "Consumible.h"
#include "Consumible_Patata.h"
#include "Consumible_Carne.h"

// CONSTRUCTOR

Consumible_Manager::Consumible_Manager() {
    
    float mult = 4.9212625;

    _consumibles.push_back( new Consumible_Carne(5,mult * 15,mult * 0,mult * 15));
    /*_consumibles.push_back( new Consumible_Carne(5,mult * 19,mult * 0,mult * 15));
    _consumibles.push_back( new Consumible_Carne(5,mult * 19,mult * 0,mult * 15));
    _consumibles.push_back( new Consumible_Carne(5,mult * 19,mult * 50,mult * 15));
    _consumibles.push_back( new Consumible_Patata(5,mult * 19,mult * 50,mult * 15));
    _consumibles.push_back( new Consumible_Patata(5,mult * 19,mult * 50,mult * 15));*/
    _consumibles.push_back( new Consumible_Patata(5,mult * 19,mult * 0,mult * 15));
}

// DESTRUCTOR

Consumible_Manager::~Consumible_Manager(){
    
 for (short i = 0; i < _consumibles.size(); ++i) {
    delete _consumibles[i];
  }
  _consumibles.clear();
  
}


// METODOS BORRAR

void Consumible_Manager::borrar_consumible(Consumible* objeto){

    std::vector<Consumible*>::iterator it;
    it = std::find(_consumibles.begin(), _consumibles.end(), objeto);
    if ( it != _consumibles.end()){
        _consumibles.erase(it);
        delete objeto;
    }
   
}

void Consumible_Manager::borrar_consumible(short id){
    delete _consumibles[id];
    _consumibles.erase(_consumibles.begin() + id);
}



/// METODOS GET 

std::vector<Consumible*>* Consumible_Manager::get_consumibles(){
    return &_consumibles;
}

