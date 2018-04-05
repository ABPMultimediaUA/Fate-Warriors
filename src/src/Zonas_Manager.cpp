#include "Zonas_Manager.h"
#include "Zona.h"
#include "Zona_Final.h"
#include "Zona_Inicial.h"
#include "Zona_Coliseo.h"
#include "Zona_Respawn_Infinito.h"

#include <iostream>

Zonas_Manager::Zonas_Manager() {

	_equipoA = 0;
	_equipoB = 0;


    // tener xml con la informacion de todos los objetos
    
	_n_zonas = 8;
	_zonas = new Zona*[_n_zonas];

    unsigned short _cont;
	float mult = 4.9212625;
//	_zonas[0] = new Zona(5*mult, 0*mult, 37*mult,20,20, Enum_Equipo_A);

	_zona_incial = new Zona_Inicial(12.5*mult, 0*mult, 12.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_A); //Zona 1
	_zonas[0] = _zona_incial ;
	_zona_bando_a.push_back(_zonas[0]);	
	
	_zonas[1]  = new Zona_Respawn_Infinito(29.5*mult, 0*mult, 28.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_B, 8); //Zona 3
	_zona_bando_b.push_back(_zonas[1]);	

	_zonas[2]  = new Zona_Coliseo(10.5*mult, 0*mult, 34.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_A,4,5);		//Zona 7
	_zona_bando_a.push_back(_zonas[2]);	
	_zonas[3]  = new Zona(10.5*mult, 0*mult, 56.5*mult,(15*mult)/2,(15*mult)/2, Enum_Equipo_B);   //Zona 10
	_zona_bando_b.push_back(_zonas[3]);	



	_zonas[4]  = new Zona(38*mult, 0*mult, 104.5*mult,(20*mult)/2,(15*mult)/2, Enum_Equipo_A);	// Zona 22
	_zona_bando_a.push_back(_zonas[4]);	

	_zonas[5]  = new Zona(34.5*mult, 0*mult, 74*mult,(25*mult)/2,(20*mult)/2, Enum_Equipo_B);	// Zona 16
	_zona_bando_b.push_back(_zonas[5]);	

	_zonas[6]  = new Zona_Final(72*mult, 0*mult, 42*mult,(25*mult)/2,(30*mult)/2, Enum_Equipo_A);	// Zona 32
	_zona_bando_a.push_back(_zonas[6]);	

	//_zonas[7]  = new Zona(57*mult, 0*mult, 101*mult,(9*mult)/2,(7*mult)/2, Enum_Equipo_A);	// Zona 24 desmasiado peque
	
	_zonas[7]   = new Zona(73.5*mult, 0*mult, 99*mult,(15*mult)/2,(20*mult)/2, Enum_Equipo_B);	// Zona 28
	_zona_bando_b.push_back(_zonas[7]);	

	_zona_bando_a_no_sindo_conquistada = _zona_bando_a;
	_zona_bando_b_no_sindo_conquistada = _zona_bando_b;

	/*
	_zonas[2]  = new Zona(38*mult, 0*mult, 35*mult,8*mult,10*mult, Enum_Equipo_B);
	_zonas[3]  = new Zona(3*mult, 0*mult, 27*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[4]  = new Zona(3*mult, 0*mult, 49*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[5]  = new Zona(3*mult, 0*mult, 82*mult,9*mult,10*mult, Enum_Equipo_A);   //NEUTRO
	_zonas[6]  = new Zona(11*mult, 0*mult, 101*mult,6*mult,10*mult, Enum_Equipo_A); //NEUTRO
	_zonas[7]  = new Zona(22*mult, 0*mult, 64*mult,25*mult,20*mult, Enum_Equipo_B);
	_zonas[8]  = new Zona(30*mult, 0*mult, 51*mult,10*mult,8*mult, Enum_Equipo_A); //NEUTRO
	_zonas[9]  = new Zona(28*mult, 0*mult, 97*mult,20*mult,15*mult, Enum_Equipo_B);
	_zonas[10]  = new Zona(54*mult, 0*mult, 47*mult,7*mult,9*mult, Enum_Equipo_A); //NEUTRO
	_zonas[11]  = new Zona(54*mult, 0*mult, 70*mult,15*mult,15*mult, Enum_Equipo_B);
	_zonas[12]  = new Zona(66*mult, 0*mult, 89*mult,15*mult,20*mult, Enum_Equipo_B);
	_zonas[13]  = new Zona(75*mult, 0*mult, 67*mult,6*mult,8*mult, Enum_Equipo_A); //NEUTRO
	_zonas[14]  = new Zona(59*mult, 0*mult, 27*mult,35*mult,35*mult, Enum_Equipo_B);
	*/

}

Zonas_Manager::~Zonas_Manager() {
    unsigned short _cont;
    
	for(_cont = 0; _cont < _n_zonas; _cont++) {
		delete _zonas[_cont];
	}
	delete [] _zonas;
}


void Zonas_Manager::actualizar_zonas(){

	_equipoA = 0;
	_equipoB = 0;

	_zona_bando_a.clear();
	_zona_bando_b.clear();
	_zona_bando_a_no_sindo_conquistada.clear();
	_zona_bando_b_no_sindo_conquistada.clear();

	for(uint8_t zona=0; zona<_n_zonas; zona++){
		_zonas[zona]->actualizar_zona();
		
		//Una vez actualizado de quien es la zona se registra su bando
		Enum_Equipo equipo = _zonas[zona]->get_equipo();
		bool conquistando = _zonas[zona]->get_conquistando();
		if (equipo == Enum_Equipo_A){
			_equipoA++;
			_zona_bando_a.push_back(_zonas[zona]);

			if(!conquistando){
				_zona_bando_a_no_sindo_conquistada.push_back(_zonas[zona]);
			}

		}
		else if (equipo == Enum_Equipo_B){
			_equipoB++;
			_zona_bando_b.push_back(_zonas[zona]);

			if(!conquistando){
				_zona_bando_b_no_sindo_conquistada.push_back(_zonas[zona]);
			}
		}


	}
	comprobar_victoria();
}

Zona** Zonas_Manager::get_zonas(){
	return _zonas;
}

unsigned short Zonas_Manager::get_n_zonas(){
	return _n_zonas;
}




Enum_Equipo Zonas_Manager::comprobar_victoria(){
	/*
	auto cantidad =calcular_cantidad_territorios_por_bando();

    std::cout << "ID: 0, "
              << "EquipoA: " << (int)std::get<0>(cantidad) << ", "
              << "EquipoB: " << (int)std::get<1>(cantidad) << ", \n";
	*/

	if(_equipoA==_n_zonas){
 		std::cout << "Gana Equipo A"<< (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_A;
	}

	else if(_equipoB==_n_zonas){
		std::cout << "Gana Equipo B"<< (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_B;
	}

	else{
		//std::cout << "AUN NO HAY VICTORIA"<< (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_Ninguno;  //Borrar ........ falta equipo neutro
	}
}

Enum_Equipo Zonas_Manager::comprobar_victoria_fin_tiempo_partida(){

	
	if(_equipoA == _equipoB){
		std::cout << "Gana empate " << (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_A;  //Borrar ........ falta equipo neutro
	}
	else if(_equipoA>_equipoB){
		std::cout << "Gana Equipo A "<< (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_A;
	}
	else{
		std::cout << "Gana Equipo B "<< (int)_equipoA << " - " <<(int)_equipoB << "\n" ;
		return Enum_Equipo_Ninguno;	
	}
}


std::tuple<uint8_t,uint8_t> Zonas_Manager::calcular_cantidad_territorios_por_bando(){
	uint8_t equipoA = 0;
	uint8_t equipoB = 0;

	for(uint8_t zona=0; zona<_n_zonas; zona++){
		Enum_Equipo equipo = _zonas[zona]->get_equipo();
		if (equipo == Enum_Equipo_A){
			equipoA++;
		}
		else if (equipo == Enum_Equipo_B){
			equipoB++;
		}
	}
	
	return std::make_tuple(equipoA,equipoB);
}


std::vector<Zona*> Zonas_Manager::get_zonas_equipo_a(){
	return _zona_bando_a;
}

std::vector<Zona*> Zonas_Manager::get_zonas_equipo_b(){
	return _zona_bando_b;
}


std::vector<Zona*> Zonas_Manager::get_zonas_equipo_a_no_siendo_conquistadas(){
	return _zona_bando_a_no_sindo_conquistada;
}

std::vector<Zona*> Zonas_Manager::get_zonas_equipo_b_no_siendo_conquistadas(){
	return _zona_bando_b_no_sindo_conquistada;
}

Vector2 Zonas_Manager::get_posicion_zona_inicial(){
	return Vector2(_zona_incial->getX(), _zona_incial->getZ());
}