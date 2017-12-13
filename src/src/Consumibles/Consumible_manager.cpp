#include "Consumible_manager.h"
#include "../Tiempo/Time.h"
#include "Consumible.h"
#include "Consumible_patata.h"
#include "Consumible_carne.h"

// CONSTRUCTOR

Consumible_manager::Consumible_manager() {
    _consumibles.push_back( new Consumible_carne(5, 100, 50, 10));
    _consumibles.push_back( new Consumible_carne(5, 10, 50, 10));
    _consumibles.push_back( new Consumible_carne(5, 1000, 50, 10));
    _consumibles.push_back( new Consumible_carne(5, 90, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 69, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 190, 50, 10));
    _consumibles.push_back( new Consumible_patata(5, 1099, 50, 10));
}

// DESTRUCTOR

Consumible_manager::~Consumible_manager(){

}


// METODOS BORRAR

void Consumible_manager::borrar_consumible(Consumible* objeto){

    std::vector<Consumible*>::iterator it;
    std::cout << "me meto aqui" << _consumibles.size() << std::endl;
    it = std::find(_consumibles.begin(), _consumibles.end(), objeto);
    if ( it != _consumibles.end()){
        _consumibles.erase(it);
        delete objeto;
    }
   
}


/// METODOS GET 

std::vector<Consumible*> Consumible_manager::get_consumibles(){
    return _consumibles;
}

