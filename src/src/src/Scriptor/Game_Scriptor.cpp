
#include "Scriptor.h"
#include "Game_Scriptor.h"

Game_Scriptor* Game_Scriptor::instancia=0;

Game_Scriptor* Game_Scriptor::Instance(){
	if(instancia==0){
	instancia= new Game_Scriptor();
	}
	return instancia;
}

Game_Scriptor::Game_Scriptor():Scriptor("hola.txt"){}