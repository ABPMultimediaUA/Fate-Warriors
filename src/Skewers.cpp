#include "Skewers.h"
#include <iostream>
Skewers::Skewers(float _i_x, float _i_y, float _i_ancho, float _i_alto) : Interactuable(_i_x, _i_y, _i_ancho, _i_alto){
	_activated = true;
	_id = 0;
	std::cout << "me meto en el constructor"<< std::endl;
}

Skewers::~Skewers() {
}
 void Skewers::change_activate_value(){
	 (_activated) = !(_activated);
 }

 bool Skewers::usar(){
	 change_activate_value();
	 return true;
 }
