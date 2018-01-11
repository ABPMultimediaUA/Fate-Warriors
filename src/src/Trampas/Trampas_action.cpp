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

     if(_minas[_cont]->explota() && comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_mina, 8)){
        _player->danyar(_minas[_cont]->get_danyo());
    } 
  }
  eliminar_trampas_mina();  
}
 
void Trampas_action::eliminar_trampas_mina(){
	_trampas->borrar_mina();
}

Pinchos** Trampas_action::comprobar_trampas_pinchos(){
  unsigned short n_trampas = _trampas->get_n_trampas_pincho();
 
  for(unsigned short _cont=0; _cont<n_trampas; _cont++) {
    
    Vector2 vec_pinchos= _pinchos[_cont]->get_vector();
    Vector2 vec_player= _player->get_vector();
    
    if(_pinchos[_cont]->puede_quitar_vida()){
      if(comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_pinchos, 6)){
        _player->danyar(_pinchos[_cont]->get_danyo());
      }
    }
  }
}
 
Charcos_electrificados** Trampas_action::comprobar_trampas_charco(){
  unsigned short n_charcos = _trampas->get_n_trampas_charco();
  
  for(unsigned short _cont=0; _cont<n_charcos; _cont++){
 
    Vector2 vec_charcos= _charcos[_cont]->get_vector();
    Vector2 vec_player= _player->get_vector();
 
    if(_charcos[_cont]->puede_quitar_vida()){
      if (comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_charcos, 12)){
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