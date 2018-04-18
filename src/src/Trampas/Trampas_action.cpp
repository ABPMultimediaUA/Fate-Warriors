#include "Trampas_action.h"

#include "../Tiempo/Time.h"
#include "Pinchos.h"
#include "Minas.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Trampas_manager.h"
#include "../Personajes/Player.h"
#include "../Personajes/NPC.h"
#include "../Personajes/NPC_Manager.h"

#include "../Utilidades/Vector.h"
#include "../Interfaz_Libs/Lib_Math.h"

#include "../Interfaz/Motor.h"

Trampas_action::Trampas_action() {
	Game* punterito = Game::game_instancia();
	Datos_Partida * datitos = punterito->game_get_datos();

	_trampas = datitos->get_trampas_manager();
	
	_pinchos = _trampas->get_trampas_pinchos();
	_minas   = _trampas->get_trampas_mina();
}

Trampas_action::~Trampas_action(){
	_pinchos = nullptr;
	_minas   = nullptr;
}


void Trampas_action::comprobar_trampas_mina(){
 
  unsigned short n_trampas = _trampas->get_n_trampas_mina();

 	Character** npc =  Game::game_instancia()->game_get_datos()->get_characters();
	uint16_t numnpc = Game::game_instancia()->game_get_datos()->get_num_characters();

  Objeto_Motor* _objeto_motor_mina;
  Motor* putero_a_motor = Motor::Motor_GetInstance();

   float x;
   float z;

  
  for(unsigned short _cont=0; _cont<n_trampas; _cont++) {
    _objeto_motor_mina = _minas[_cont]->get_objeto_motor();

     Vector2 vec_mina= _minas[_cont]->get_vector();
      for (short i=0; i<numnpc; i++){

        if( npc[i]->get_vida_actual()>0){
          Vector2 vec_npc= npc[i]->get_vector();
      
            if(_minas[_cont]->explota()){ 
                if (comprobar_colision_teniendo_tambien_radio(vec_npc, 2, vec_mina, 20)){
                    x = vec_npc._x - vec_mina._x;
                    z = vec_npc._y - vec_mina._y;

                    Vector2 direccion_impulso(x,z);
                    direccion_impulso.Normalize();

                    float valor = lib_math_distancia_2_puntos(vec_npc._x, vec_npc._y, vec_mina._x, vec_mina._y);
                    npc[i]->danyar(_minas[_cont]->get_danyo()*(1/valor));
                    
                    if(valor<2.5){valor=2.5;}
                  
                    Vector3 a(direccion_impulso._x*(40000/valor),0,direccion_impulso._y*(40000/valor));
                    npc[i]->get_objeto_motor()->Impulso_explosion(a);
                }
            }

           else if(putero_a_motor->comprobar_colision(_objeto_motor_mina->getRigidBody(), npc[i]->get_objeto_motor()->getRigidBody())){
              if(!_minas[_cont]->get_estado()){
                _minas[_cont]->activar();
              }     
          }
        }
      }      
  }
        eliminar_trampas_mina();  
}
 
void Trampas_action::eliminar_trampas_mina(){
	_trampas->borrar_mina();
}

Pinchos** Trampas_action::comprobar_trampas_pinchos(){
  unsigned short n_trampas           = _trampas->get_n_trampas_pincho();
  Objeto_Motor* _objeto_motor_pinchos;
  Motor* putero_a_motor              = Motor::Motor_GetInstance();

 	Character** npc =  Game::game_instancia()->game_get_datos()->get_characters();
	uint16_t numnpc = Game::game_instancia()->game_get_datos()->get_num_characters();


  for(unsigned short _cont=0; _cont<n_trampas; _cont++) {
    
    _objeto_motor_pinchos = _pinchos[_cont]->get_objeto_motor();
    
    if(_pinchos[_cont]->puede_quitar_vida()){
      
      for (short i=0; i<numnpc; i++){   

        if(npc[i]->get_vida_actual()>0 && putero_a_motor->comprobar_colision(_objeto_motor_pinchos->getRigidBody(), npc[i]->get_objeto_motor()->getRigidBody())){
          npc[i]->danyar(_pinchos[_cont]->get_danyo());
        }
      }

      
    }
  }
}

void Trampas_action::update(){
	comprobar_trampas_mina();
	comprobar_trampas_pinchos();
}