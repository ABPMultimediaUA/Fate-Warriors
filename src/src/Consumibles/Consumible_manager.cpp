#include "Consumible_manager.h"
#include "../Tiempo/Time.h"
#include "Consumible.h"
#include "Consumible_patata.h"
#include "Consumible_carne.h"

// CONSTRUCTOR

Consumible_manager::Consumible_manager() {
    _consumibles.push_back( new Consumible_carne(5, 30, 230, 0));
    _consumibles.push_back( new Consumible_carne(5, 10, 50, 10));
    _consumibles.push_back( new Consumible_carne(5, 1000, 50, 10));
    _consumibles.push_back( new Consumible_carne(5, 90, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 69, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 190, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 1099, 50, 10));
}

// DESTRUCTOR

Consumible_manager::~Consumible_manager(){
    
 for (short i = 0; i < _consumibles.size(); ++i) {
    delete _consumibles[i];
  }
  _consumibles.clear();
  
}


// METODOS BORRAR

void Consumible_manager::borrar_consumible(Consumible* objeto){

    std::vector<Consumible*>::iterator it;
    it = std::find(_consumibles.begin(), _consumibles.end(), objeto);
    if ( it != _consumibles.end()){
        _consumibles.erase(it);
        delete objeto;
    }
   
}

void Consumible_manager::borrar_consumible(short id){
    delete _consumibles[id];
    _consumibles.erase(_consumibles.begin() + id);
}



/// METODOS GET 

std::vector<Consumible*>* Consumible_manager::get_consumibles(){
    return &_consumibles;
}

