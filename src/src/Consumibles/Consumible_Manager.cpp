#include "Consumible_Manager.h"

#include "Consumible.h"
#include "Consumible_Patata.h"
#include "Consumible_Carne.h"
#include "Consumible_Agua.h"
#include "Consumible_Power_Up.h"
#include "Consumible_Fuerza.h"
#include "Consumible_Vida_Infinita.h"
#include "Enum_Tipo_Consumible.h"

#include "../Zonas/Respawn.h"
#include "../Tiempo/Time.h"


// CONSTRUCTOR

Consumible_Manager::Consumible_Manager() {
    
    mult = 4.9212625;

    _consumibles_a_reusar.push_back( new Consumible_Carne(5,mult*170, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Carne(5,mult*150, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Carne(5,mult*170, mult*99999, mult*50));
    _consumibles_a_reusar.push_back( new Consumible_Carne(5,mult*150, mult*99999, mult*50));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*600, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*400, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*600, mult*99999, mult*50));
    _consumibles_a_reusar.push_back( new Consumible_Patata(5,mult*400, mult*99999, mult*50));
    _consumibles_a_reusar.push_back( new Consumible_Agua(5,mult*600, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Agua(5,mult*400, mult*99999, mult*52));
    _consumibles_a_reusar.push_back( new Consumible_Agua(5,mult*600, mult*99999, mult*50));
    _consumibles_a_reusar.push_back( new Consumible_Agua(5,mult*400, mult*99999, mult*50));

 //   _consumibles.push_back( new Consumible_Fuerza(5,mult*6, mult*0, mult*52));


    numero_max = 0;


}



// DESTRUCTOR

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

void Consumible_Manager::borrar_consumible(Consumible_Power_Up* objeto){
    std::vector<Consumible*>::iterator it;
    it = std::find(_consumibles.begin(), _consumibles.end(), objeto);
    
    if ( it != _consumibles.end()){
        objeto->setPositionXZ(999999,99999);
        _consumibles.erase(it);
        _consumibles_a_reusar.push_back(objeto);
        delete objeto;
    }
   
}

void Consumible_Manager::borrar_consumible(short id){
    
   // delete _consumibles[id];
   _consumibles[id]->setPositionXZ(999999,99999);
    _consumibles_a_reusar.push_back(_consumibles[id]);
    _consumibles.erase(_consumibles.begin() + id);
    
}

// Metodo para crear los consumibles en posiciones al azar, crea la cantidad que esta determiannda por numero_max

void Consumible_Manager::crear_todos_consumibles_que_faltan(){
  
    for(uint16_t i=_consumibles.size(); i<numero_max; i++){
        Vector2 posicion = crear_posiciones_aleatorias();
       anyadir_consumible(posicion);
    }
}


//---------------------------------- MAPEADOS PARA LOS CONSUMIBLES --------------------------//

	// Funciones para guardar los datos
	struct MapeadConsumibles{			// Declaracion de los parametros
		Enum_Nombre_Consumibles _nombre_objeto;
		void (Consumible_Manager::*pmet)(Vector2);
	};

	MapeadConsumibles mapping_tipo_consumible_creada[] = {	// Definicion de los parametros
			{Nombre_Consumible_Carne, &Consumible_Manager::anyadir_consumible_carne},
			{Nombre_Consumible_Patata, &Consumible_Manager::anyadir_consumible_patata},
            {Nombre_Consumible_Nada, 0}
	};
	

//Anyade un unico consumible al vector de consumibles generando uno de un tipo al azar con un rand
void Consumible_Manager::anyadir_consumible(Vector2 posicion){

    //Comprobar que power up va a crear 

    if (_consumibles_a_reusar.size()>0){
        _consumibles_a_reusar[0]->setPositionXZ(posicion._x, posicion._y);
        _consumibles.push_back(_consumibles_a_reusar[0]);
        _consumibles_a_reusar.erase(_consumibles_a_reusar.begin());
    }

    /*
    MapeadConsumibles *_mapeado_clase = mapping_tipo_consumible_creada;

	
    Enum_Nombre_Consumibles _consumible ; //= static_cast<Enum_Nombre_Consumibles>(rand() % Nombre_Consumible_Nada);
    
    uint16_t _num = (rand() % 100);
    if (_num>15){                            // 5% de posibilidades consumible carne
        _consumible = Nombre_Consumible_Nada;
    }
    else if(_num>10){                      // 10 % de posibilidades consumible patata
        _consumible = Nombre_Consumible_Patata;
    }
    else{
        _consumible = Nombre_Consumible_Carne;
    }

	while(_mapeado_clase->_nombre_objeto!=Nombre_Consumible_Nada){
		if(_consumible == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)(posicion);
		}
		++_mapeado_clase;   
	}

    */
}





void Consumible_Manager::anyadir_consumible_patata(Vector2 posicion){
     _consumibles.push_back( new Consumible_Patata(5,posicion._x, 0, posicion._y));
}


void Consumible_Manager::anyadir_consumible_carne(Vector2 posicion){
     _consumibles.push_back( new Consumible_Carne(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_agua(Vector2 posicion){
     _consumibles.push_back( new Consumible_Agua(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_fuerza(Vector2 posicion){
     _consumibles.push_back( new Consumible_Fuerza(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_inmunidad(Vector2 posicion){
     _consumibles.push_back( new Consumible_Vida_Infinita(5,posicion._x, 0, posicion._y));
}

Vector2 Consumible_Manager::crear_posiciones_aleatorias(){
    return Respawn::posiciones_instancia()->generar_posicion_al_azar_xz();
}

/// METODOS GET 

std::vector<Consumible*>* Consumible_Manager::get_consumibles(){
    return &_consumibles;
}