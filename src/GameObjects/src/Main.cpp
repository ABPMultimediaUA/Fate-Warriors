#include <iostream>
#include "Armas/Arma_cerca.h"
#include "Armas/Arma_distancia.h"
#include "Inventario.h"
#include "Player.h"
#include "Consumibles/Consumible.h"
#include "Scriptor/Game_Scriptor.h"
#include "Armas/AD_Pistola.h"

#include "Objeto.h"
#include <list>

int main(){

	short vida = 0;


	AD_Pistola* pisto = new AD_Pistola(15,15,15,15);
	



	Arma_cerca * hola = new Arma_cerca (15,15,15,15,15,56,15,56);
	Arma_distancia * soydedistancia = new Arma_distancia (15,15,15,15,15,56,15,56);
	std::cout << hola << std::endl;
	std::cout << soydedistancia << std::endl;

	Player* jugador = new Player(5,0,2000,50);
//	delete soydedistancia;
//	delete hola;

	Game_Scriptor* lector = Game_Scriptor::Instance();
	short ametralladora = script->Dame_valor_de("Ametralladora_tipo");
	std::cout << "ta cosa funsiona" << ametralladora << std::endl;
	Scriptor *ey= new Scriptor("hola.txt");
	Inventario * cosa = new Inventario();
	cosa->cambiar_objeto_cerca(hola);
	cosa->cambiar_objeto_cerca(hola);
	cosa->cambiar_objeto_distancia(soydedistancia);

	//if(cosa->usar)
		vida = vida;


	cosa->cambiar_seleccionado();
	cosa->usar();
std::cout<< pisto->get_tipo();
	std::cout << "ta cosa funsiona" << ametralladora << std::endl;


	return 0;
}

