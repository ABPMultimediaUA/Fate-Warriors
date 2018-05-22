#include "Consumible_Manager.h"

#include "Consumible.h"
#include "Consumible_Patata.h"
#include "Consumible_Carne.h"
#include "Consumible_Agua.h"
#include "Enum_Tipo_Consumible.h"

#include "../Zonas/Respawn.h"
#include "../Tiempo/Time.h"


// CONSTRUCTOR
Consumible_Manager::Consumible_Manager() {
    
    float mult = 4.9212625;

    _consumibles_a_reusar.push_back( new Consumible_Carne(5,mult*4000, 0, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*4000, 0, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*6000, 0, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*5000, 0, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Agua(5,mult*6000, 0, mult*52));

}

// DESTRUCTOR
//Elimina los consumibles que estan en uso
// Elimina los consumibles dde la lista de objetos a reaparecer
Consumible_Manager::~Consumible_Manager(){
  
    for (short i = 0; i < _consumibles.size(); i++) {
        delete _consumibles[i];
    }
    _consumibles.clear();

    for (short i = 0; i < _consumibles_a_reusar.size(); i++) {
        delete _consumibles_a_reusar[i];
    }
    _consumibles_a_reusar.clear();
}


// METODOS BORRAR
// Pone en la lista de objetos a reutilizar
void Consumible_Manager::borrar_consumible(short id){
    _consumibles[id]->setPositionXZ(999999,99999);
    _consumibles_a_reusar.push_back(_consumibles[id]);
    _consumibles.erase(_consumibles.begin() + id);
}


//Anyade un unico consumible al vector de consumibles generando uno de un tipo al azar con un rand
//Comprueba si se puede crear consumibles con una probabilidad del 5% de que se cree
void Consumible_Manager::anyadir_consumible(Vector2 posicion){

    uint16_t _num = (rand() % 100);

    if (_num<4){               
        if (_consumibles_a_reusar.size()>0){   
            _consumibles_a_reusar[0]->setPositionXZ(posicion._x, posicion._y);
            _consumibles_a_reusar[0]->set_tiempo_espera();
            _consumibles.push_back(_consumibles_a_reusar[0]);
            _consumibles_a_reusar.erase(_consumibles_a_reusar.begin());
        }
    }

}

/// METODOS GET 
// Devuelve el puntero al vector de los consumibles
std::vector<Consumible*>* Consumible_Manager::get_consumibles(){
    return &_consumibles;
}