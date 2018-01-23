#include "Trampas_action.h"
#include "../Tiempo/Time.h"
#include "Pinchos.h"
#include "Minas.h"
#include "Charcos_electrificados.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Trampas_manager.h"
#include "../Personajes/Player.h"
#include "../Utilidades/Vector.h"
#include "../Interfaz/Motor.h"

Trampas_action::Trampas_action() {
	Game* punterito = Game::game_instancia();
	Datos_Partida * datitos = punterito->game_get_datos();

	_player = datitos->get_player();
	_trampas = datitos->get_trampas_manager();
	
	_pinchos = _trampas->get_trampas_pinchos();
	_minas   = _trampas->get_trampas_mina();
	_charcos = _trampas->get_trampas_charco();
}

Trampas_action::~Trampas_action(){
	_pinchos = nullptr;
	_charcos = nullptr;
	_minas   = nullptr;
}


void Trampas_action::comprobar_trampas_mina(){
 
  unsigned short n_trampas = _trampas->get_n_trampas_mina();
  
  for(unsigned short _cont=0; _cont<n_trampas; _cont++) {
    Vector2 vec_mina= _minas[_cont]->get_vector();
    Vector2 vec_player= _player->get_vector();
 
    if(comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_mina, 2)){
      if(!_minas[_cont]->get_estado()){
        _minas[_cont]->activar();
      }     
    }

     if(_minas[_cont]->explota()){ 
        if (comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_mina, 8)){
            _player->danyar(_minas[_cont]->get_danyo());
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
  Objeto_Motor* _objeto_motor_player = _player->get_objeto_motor();
  Objeto_Motor* _objeto_motor_pinchos;
  Motor* putero_a_motor              = Motor::Motor_GetInstance();

  for(unsigned short _cont=0; _cont<n_trampas; _cont++) {
    
    _objeto_motor_pinchos = _pinchos[_cont]->get_objeto_motor();
    
    if(_pinchos[_cont]->puede_quitar_vida()){
      if(putero_a_motor->comprobar_colision(_objeto_motor_pinchos->getRigidBody(),_objeto_motor_player->getRigidBody())){
        _player->danyar(_pinchos[_cont]->get_danyo());
      }
    }
  }
}
 
Charcos_electrificados** Trampas_action::comprobar_trampas_charco(){
  
  unsigned short n_charcos = _trampas->get_n_trampas_charco();
  Objeto_Motor* _objeto_motor_player = _player->get_objeto_motor();
  Objeto_Motor* _objeto_motor_charco;
  Motor* putero_a_motor              = Motor::Motor_GetInstance();
  
  for(unsigned short _cont=0; _cont<n_charcos; _cont++){
 
   _objeto_motor_charco = _charcos[_cont]->get_objeto_motor();
 
    if(_charcos[_cont]->puede_quitar_vida()){
       if(putero_a_motor->comprobar_colision(_objeto_motor_charco->getRigidBody(),_objeto_motor_player->getRigidBody())){
        _player->danyar(_charcos[_cont]->get_danyo());
      }
    }
  }
}

void Trampas_action::update(){
	comprobar_trampas_charco();
	comprobar_trampas_mina();
	comprobar_trampas_pinchos();
}