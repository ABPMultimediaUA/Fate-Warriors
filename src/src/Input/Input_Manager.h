#ifndef SRC_INPUT_MANAGER_H_
#define SRC_INPUT_MANAGER_H_

#include "SFML/Graphics.hpp"

#include <cstdint>

// Ya lo haré

/*
enum Enum_Inputs {
	Input_Arriba,
	Input_Abajo,
	Input_Izquierda,
	Input_Derecha,
	Input_Dash,
	Input_Salto,
	Input_Interactuar,
	Input_Usar_Arma,
	Input_Ataque_Normal,
	Input_Ataque_Fuerte,
	Input_Camara_Arriba,
	Input_Camara_Abajo,
	Input_Camara_Izquierda,
	Input_Camara_Derecha,
	Input_Centrar_Camara,
	Input_Pausa,
	N_Inputs,
	Ninguno
};*/

class Input_Manager {
public:
	Input_Manager();
	~Input_Manager();

	void recibe_input();

private:
	uint8_t _movimiento;

};

#endif /* SRC_INPUT_MANAGER_H_ */