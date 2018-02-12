#include "Consumible_Manager.h"
#include "../Tiempo/Time.h"
#include "Consumible.h"
#include "Consumible_Patata.h"
#include "Consumible_Carne.h"
#include "Consumible_Agua.h"

#include "Consumible_Power_Up.h"
#include "Consumible_Fuerza.h"
#include "Consumible_Vida_Infinita.h"
#include "../Nivel/Nivel.h"
#include "../Tiempo/Time.h"

// CONSTRUCTOR

Consumible_Manager::Consumible_Manager() {
    
    float mult = 4.9212625;

//    _consumibles.push_back( new Consumible_Carne(5,mult*17, mult*0, mult*52));

    _consumibles.push_back( new Consumible_Carne(5,mult*15, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Carne(5,mult*17, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Carne(5,mult*15, mult*0, mult*50));

   // _consumibles.push_back( new Consumible_Patata(5,mult*6, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Patata(5,mult*4, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Patata(5,mult*6, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Patata(5,mult*4, mult*0, mult*50));

   // _consumibles.push_back( new Consumible_Agua(5,mult*6, mult*0, mult*52));
  /*  _consumibles.push_back( new Consumible_Agua(5,mult*4, mult*0, mult*52));
    _consumibles.push_back( new Consumible_Agua(5,mult*6, mult*0, mult*50));
    _consumibles.push_back( new Consumible_Agua(5,mult*4, mult*0, mult*50));
*/
    _consumibles.push_back( new Consumible_Fuerza(5,mult*6, mult*0, mult*52));

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
        
        _consumibles.push_back( new Consumible_Patata(5,posiciones_de_respawn_consumibles[i][0], mult*0, posiciones_de_respawn_consumibles[i][1]));
    }

    _reloj = Time::Instance();     
    _tiempo_ultimo_creado = _reloj->get_current();  
}

// DESTRUCTOR

Consumible_Manager::~Consumible_Manager(){
    
 for (short i = 0; i < _consumibles.size(); i++) {
    delete _consumibles[i];
  }
  _consumibles.clear();

  for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;
  
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


void Consumible_Manager::crear_consumibles_en_posiciones_aleatorias(){
/*
    if(posiciones_resp_por_usar.size()>0&&_reloj->get_current()>tiempo_resp_por_usar[0]){
        _consumibles.push_back( new Consumible_Carne(5,posiciones_resp_por_usar[0]._x, 0, posiciones_resp_por_usar[0]._y));
        posiciones_resp_por_usar.erase(posiciones_resp_por_usar.begin());
        tiempo_resp_por_usar.erase(tiempo_resp_por_usar.begin());
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
/// METODOS GET 

std::vector<Consumible*>* Consumible_Manager::get_consumibles(){
    return &_consumibles;
}

