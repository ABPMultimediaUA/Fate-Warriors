#include "Consumible_Manager.h"
#include "../Tiempo/Time.h"
#include "Consumible.h"
#include "Consumible_Patata.h"
#include "Consumible_Carne.h"
#include "Consumible_Agua.h"

#include "Consumible_Power_Up.h"
#include "Consumible_Fuerza.h"
#include "Consumible_Vida_Infinita.h"
#include "../Respawn.h"
#include "../Tiempo/Time.h"
#include "Enum_Tipo_Consumible.h"


// CONSTRUCTOR

Consumible_Manager::Consumible_Manager() {
    
    mult = 4.9212625;

/*    _consumibles.push_back( new Consumible_Carne(5,mult*17, mult*0, mult*52));

    _consumibles.push_back( new Consumible_Carne(5,mult*15, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Carne(5,mult*17, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Carne(5,mult*15, mult*0, mult*50));

    _consumibles.push_back( new Consumible_Patata(5,mult*6, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Patata(5,mult*4, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Patata(5,mult*6, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Patata(5,mult*4, mult*0, mult*50));

    _consumibles.push_back( new Consumible_Agua(5,mult*6, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Agua(5,mult*4, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Agua(5,mult*6, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Agua(5,mult*4, mult*0, mult*50));
*/
    _consumibles.push_back( new Consumible_Fuerza(5,mult*6, mult*0, mult*52));


    numero_max = 2;


    _reloj = Time::Instance();     
    _tiempo_ultimo_creado = _reloj->get_current();  
}



// DESTRUCTOR

Consumible_Manager::~Consumible_Manager(){
    
 for (short i = 0; i < _consumibles.size(); i++) {
    delete _consumibles[i];
  }
  _consumibles.clear();

}




// METODOS BORRAR

void Consumible_Manager::borrar_consumible(Consumible_Power_Up* objeto){
    std::vector<Consumible*>::iterator it;
    it = std::find(_consumibles.begin(), _consumibles.end(), objeto);
    
    if ( it != _consumibles.end()){
        _consumibles.erase(it);
        delete objeto;
    }
   
}

void Consumible_Manager::borrar_consumible(short id){
   
   Vector2 pos(_consumibles[id]->getX(), _consumibles[id]->getZ());
   posiciones_resp_por_usar.push_back(pos);
   _tiempo_ultimo_creado = _reloj->get_current()+500;
   tiempo_resp_por_usar.push_back(_tiempo_ultimo_creado);

    delete _consumibles[id];
    _consumibles.erase(_consumibles.begin() + id);
}

// Metodo para crear los consumibles en posiciones al azar, crea la cantidad que esta determiannda por numero_max

void Consumible_Manager::crear_todos_consumibles_que_faltan(){
  
    for(uint16_t i=_consumibles.size(); i<numero_max; i++){
    std::cout << "aparece consumible \n";
       anyadir_consumible();
    }
}


//---------------------------------- MAPEADOS PARA LOS CONSUMIBLES --------------------------//

	// Funciones para guardar los datos
	struct MapeadConsumibles{			// Declaracion de los parametros
		Enum_Nombre_Consumibles _nombre_objeto;
		void (Consumible_Manager::*pmet)();
	};

	MapeadConsumibles mapping_tipo_consumible_creada[] = {	// Definicion de los parametros
			{Nombre_Consumible_Agua, &Consumible_Manager::anyadir_consumible_agua},
			{Nombre_Consumible_Carne, &Consumible_Manager::anyadir_consumible_carne},
			{Nombre_Consumible_Fuerza, &Consumible_Manager::anyadir_consumible_fuerza},
			{Nombre_Consumible_Patata, &Consumible_Manager::anyadir_consumible_patata},
			{Nombre_Consumible_Vida_Infinita, &Consumible_Manager::anyadir_consumible_patata},
            {Nombre_Consumible_Nada, &Consumible_Manager::anyadir_consumible_patata}
	};
	

//Anyade un unico consumible al vector de consumibles generando uno de un tipo al azar con un rand
void Consumible_Manager::anyadir_consumible(){

    //Comprobar que power up va a crear 
    MapeadConsumibles *_mapeado_clase = mapping_tipo_consumible_creada;
	Enum_Nombre_Consumibles _arma = static_cast<Enum_Nombre_Consumibles>(rand() % Nombre_Consumible_Nada);

	while(_mapeado_clase->_nombre_objeto!=Nombre_Consumible_Nada){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;   
	}
}

void Consumible_Manager::anyadir_consumible_patata(){
    Vector2 posicion = crear_posiciones_aleatorias();
     _consumibles.push_back( new Consumible_Patata(5,posicion._x, 0, posicion._y));
}


void Consumible_Manager::anyadir_consumible_carne(){
    Vector2 posicion = crear_posiciones_aleatorias();
     _consumibles.push_back( new Consumible_Carne(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_agua(){
    Vector2 posicion = crear_posiciones_aleatorias();
     _consumibles.push_back( new Consumible_Agua(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_fuerza(){
     Vector2 posicion = crear_posiciones_aleatorias();
     _consumibles.push_back( new Consumible_Fuerza(5,posicion._x, 0, posicion._y));
}

void Consumible_Manager::anyadir_consumible_inmunidad(){
     Vector2 posicion = crear_posiciones_aleatorias();
     _consumibles.push_back( new Consumible_Vida_Infinita(5,posicion._x, 0, posicion._y));
}

Vector2 Consumible_Manager::crear_posiciones_aleatorias(){
    return Respawn::posiciones_instancia()->generar_posicion_al_azar_xz();
}

/// METODOS GET 

std::vector<Consumible*>* Consumible_Manager::get_consumibles(){
    return &_consumibles;
}

