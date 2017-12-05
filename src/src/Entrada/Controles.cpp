#include "SFML/Graphics.hpp"
#include "Controles.h"
#include "Input.h"



Controles* Controles::instancia=0;

Controles* Controles::Instance(){
	if(instancia==0){
	instancia= new Controles();
	}
	return instancia;
}


Controles::Controles(){}
Controles::~Controles(){}


bool Controles::estaPulsada(Input_key key){
	//W:22  ||A:0  ||D:3  ||S:18  ||esc: 36
	switch(key){
		case 22: //W
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				return true;
			}
			break;
		
		case 18: //S
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				return true;
			}
			break;

		case 0: //A
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				return true;
			}
			break;
		
		case 3: //D
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				return true;
			}
			break;

		case 36: //ESC
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				return true;
			}
			break;

	}
	return false;
}