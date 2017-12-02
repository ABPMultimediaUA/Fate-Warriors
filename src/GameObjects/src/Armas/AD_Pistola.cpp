#include "AD_Pistola.h"
#include <iostream>
//#include <list>
#include "../Scriptor/Game_Scriptor.h"

AD_Pistola::AD_Pistola(short _id, float _i_x, float _i_y, float _i_z) 
: Arma_distancia(_id, _i_x, _i_y, _i_z, 
					script->Dame_valor_de("Pistola_tipo"), 
					script->Dame_valor_de("Pistola_usos"), 
					script->Dame_valor_de("Pistola_frecuencia"), 
					script->Dame_valor_de("Pistola_rango")){}

AD_Pistola::~AD_Pistola(){
	
}

bool AD_Pistola::usar(){
	if (decrease_uses()){
		return true;
	}

	return false;
}


void AD_Pistola::update(){
}


void AD_Pistola::render(){

}
