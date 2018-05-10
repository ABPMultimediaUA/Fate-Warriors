#ifndef SRC_MENU_PAUSA_H_
#define SRC_MENU_PAUSA_H_

class Opcion;
class Input;

#include <cstdint>

// 3 opciones en este menu
const uint8_t _n_opciones_pausa = 3;

class Menu_Pausa {
public:
	Menu_Pausa(Input* _i_input);
	~Menu_Pausa();

	void update(double _i_tiempo);

	void set_tiempo_pausa();
	uint8_t get_i_opcion();
	bool menu_opciones_abierto();
	uint8_t get_i_configuracion();

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_PAUSA_H_ */