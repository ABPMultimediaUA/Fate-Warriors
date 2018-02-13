#include "Respawn_Points.h"
#include "../Tiempo/Time.h"

#include "../Nivel/Nivel.h"
#include "Consumible_Manager.h"
#include "../Armas/Armas_Manager.h"
#include "../Datos_Partida.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Personajes/Enum_Tipo_Ataque.h"
#include "Enum_Tipo_Consumible.h"

// CONSTRUCTOR

Respawn_Points::Respawn_Points() {

    _reloj = Time::Instance();
    
    numero_max = 16;

    Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
   
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);

    uint8_t posicion_al_azar;

    float** posiciones_de_respawn_consumibles = new float*[numero_max];
    for(uint16_t i=0; i<numero_max; i++){
        posiciones_de_respawn_consumibles[i] = new float[2];
        posicion_al_azar=rand() % cantidad_de_posiciones;
        posiciones_de_respawn_consumibles[i][0] = posiciones[posicion_al_azar][0];
        posiciones_de_respawn_consumibles[i][1] = posiciones[posicion_al_azar][1];
        
       // _consumibles.push_back( new Consumible_Agua(5,posiciones_de_respawn_consumibles[i][0], 0, posiciones_de_respawn_consumibles[i][1]));
    }   
    
}

// DESTRUCTOR

Respawn_Points::~Respawn_Points(){
    
  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;
  
}

void Respawn_Points::anyadir_nuevo_punto(Vector2 posicion){
    posiciones_resp_por_usar.push_back(posicion);
    tiempo_resp_por_usar.push_back(_reloj->get_current()+500); 
} 

/*
//---------------------------------- MAPEADOS PARA LOS CONSUMIBLES --------------------------//

	// Funciones para guardar los datos
	struct MapeadConsumibles{			// Declaracion de los parametros
		Enum_Nombre_Consumibles _nombre_objeto;
		void (Respawn_Points::*pmet)(Consumible_Manager*);
	};

	MapeadConsumibles mapping_tipo_consumible_creada[] = {	// Definicion de los parametros
			{Nombre_Consumible_Agua, &Respawn_Points::crear_consumible_agua},
			{Nombre_Consumible_Carne, &Respawn_Points::crear_consumible_carne},
			{Nombre_Consumible_Fuerza, &Respawn_Points::crear_consumible_fuerza},
			{Nombre_Consumible_Patata, &Respawn_Points::crear_consumible_patata},
			{Nombre_Consumible_Vida_Infinita, &Respawn_Points::crear_consumible_patata},
            {Nombre_Consumible_Nada, &Respawn_Points::crear_consumible_patata}
	};
	
void Respawn_Points::anyadir_power_up(){
    std::cout << "CREA UN POWER UP  \n";

    Game* punterito 		= Game::game_instancia();
	Datos_Partida * datitos	= punterito->game_get_datos();
	_consumible_manager 	= datitos->get_Consumible_Manager();

   // _consumible_manager->anyadir_consumible_patata(posiciones_resp_por_usar[0]);
    
    //Comprobar que arma va a crear
    MapeadConsumibles *_mapeado_clase = mapping_tipo_consumible_creada;
	Enum_Nombre_Consumibles _arma = static_cast<Enum_Nombre_Consumibles>(rand() % Nombre_Consumible_Nada);

	while(_mapeado_clase->_nombre_objeto!=Nombre_Consumible_Nada){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)(_consumible_manager);
		}
		++_mapeado_clase;   
	}




    posiciones_resp_por_usar.erase(posiciones_resp_por_usar.begin());
    tiempo_resp_por_usar.erase(tiempo_resp_por_usar.begin());

}


//---------------------------------- MAPEADOS PARA LAS ARMAS --------------------------//

	// Funciones para guardar los datos
	struct MapeadArmas{			// Declaracion de los parametros
		Enum_Nombre_Arma _nombre_objeto;
		void (Respawn_Points::*pmet)(Armas_Manager*);
	};

	MapeadArmas mapping_tipo_arma_creada[] = {	// Definicion de los parametros
			{Nombre_Arma_Katana, &Respawn_Points::crear_katana},
			{Nombre_Arma_Ametralladora, &Respawn_Points::crear_ametralladora},
			{Nombre_Arma_Arco, &Respawn_Points::crear_pistola},
			{Nombre_Arma_Bazooka, &Respawn_Points::crear_pistola},
			{Nombre_Arma_Pistola, &Respawn_Points::crear_pistola},
			{Nombre_Arma_Nada, &Respawn_Points::crear_pistola}
	};


void Respawn_Points::anyadir_arma(){
    std::cout << " CREA UN ARMA \n" ;
    
    Game* punterito 		= Game::game_instancia();
	Datos_Partida * datitos	= punterito->game_get_datos();
	Armas_Manager* _armas_manager 	= datitos->get_armas_manager();


    //Comprobar que arma va a crear
    MapeadArmas *_mapeado_clase = mapping_tipo_arma_creada;
	Enum_Nombre_Arma _arma = static_cast<Enum_Nombre_Arma>(rand() % Nombre_Arma_Nada);

	while(_mapeado_clase->_nombre_objeto!=Nombre_Arma_Nada){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)(_armas_manager);
		}
		++_mapeado_clase;   
	}


    posiciones_resp_por_usar.erase(posiciones_resp_por_usar.begin());
    tiempo_resp_por_usar.erase(tiempo_resp_por_usar.begin());
}

void Respawn_Points::generar_tipo_de_elemento(){

    if(posiciones_resp_por_usar.size()>0 && _reloj->get_current()>tiempo_resp_por_usar[0]){
        bool esArma = (rand() % 100) < 70;
        if(esArma){
            anyadir_arma();
        }
        else{
            anyadir_power_up();
        }
    }
}



void Respawn_Points::crear_ametralladora(Armas_Manager* _armas__manager){
    _armas__manager->crear_ametralladora(posiciones_resp_por_usar[0]);
}

void Respawn_Points::crear_pistola(Armas_Manager* _armas__manager){
    _armas__manager->crear_pistola(posiciones_resp_por_usar[0]);
}

void Respawn_Points::crear_katana(Armas_Manager* _armas__manager){
    _armas__manager->crear_katana(posiciones_resp_por_usar[0]);
}


void Respawn_Points::crear_consumible_patata(Consumible_Manager* _consumible_manager_){
    _consumible_manager_->anyadir_consumible_patata(posiciones_resp_por_usar[0]);
}

void Respawn_Points::crear_consumible_carne(Consumible_Manager* _consumible_manager_){
    _consumible_manager_->anyadir_consumible_carne(posiciones_resp_por_usar[0]);
}

void Respawn_Points::crear_consumible_agua(Consumible_Manager* _consumible_manager_){
    _consumible_manager_->anyadir_consumible_agua(posiciones_resp_por_usar[0]);
}

void Respawn_Points::crear_consumible_fuerza(Consumible_Manager* _consumible_manager_){
    _consumible_manager_->anyadir_consumible_fuerza(posiciones_resp_por_usar[0]);
}
*/