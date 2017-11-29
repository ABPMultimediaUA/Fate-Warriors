#include <iostream>
#include "Arma_cerca.h"
#include "Arma_distancia.h"
#include "Inventario.h"
#include "Consumible.h"

#include "Objeto.h"
#include <list>

int main(){

	/*
	std::list<Objeto*> arrayObjetos;
	Mina *hola = new Mina(15, 15, 15, 15, 15);
	Pistola *pisto = new Pistola(15,15,15,15,15, 6);
	arrayObjetos.push_back(hola);
	arrayObjetos.push_back(pisto);

	pisto->usar();
	pisto->usar();
	pisto->usar();
	pisto->usar();
	*/


	short vida = 0;

	Arma_cerca * hola = new Arma_cerca (15,15,15,15,56);
	Arma_distancia * soydedistancia = new Arma_distancia (15,15,15,15,56);
	Consumible * consum = new Consumible(15,15,15,15,56);

	std::cout << hola << std::endl;
	std::cout << soydedistancia << std::endl;

//	delete soydedistancia;
//	delete hola;

	Inventario * cosa = new Inventario();
	cosa->cambiar_objeto_cerca(hola);
	cosa->cambiar_objeto_cerca(hola);
	cosa->cambiar_objeto_distancia(soydedistancia);
	cosa->cambiar_consumbible(consum);

	//if(cosa->usar)
		vida = vida;

	while(cosa->usar()){
	}
	cosa->cambiar_seleccionado();
	cosa->usar();


	return 0;
}

