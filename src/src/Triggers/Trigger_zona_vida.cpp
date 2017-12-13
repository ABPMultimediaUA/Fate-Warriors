
#include "Trigger_zona_vida.h"
#include <iostream>

Trigger_zona_vida::Trigger_zona_vida(Vector2 _i_posicion) : TriggerRegion_space(_i_posicion, 50), _iHealthGiven(50) {}


void Trigger_zona_vida::Trys(Character* pBot){
											// pBot->BRadius()		
std::cout << "POSICION     ->>>>>>>>>" << pBot->get_vector()._x << pBot->get_vector()._y << std::endl;			
std::cout << "ESTA ACTIVA  ->>>>>>>>>" << esta_activa();							
  if (esta_activa() && esta_tocando(pBot->get_vector(), 59)){
	    pBot->modificar_vida_en(_iHealthGiven);
	    std::cout << "se mete" << std::endl;
	    //desactivar();
  } 
}

void Trigger_zona_vida::Render(){

}