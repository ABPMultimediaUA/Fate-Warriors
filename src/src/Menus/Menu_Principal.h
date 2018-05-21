#ifndef SRC_MENU_PRINCIPAL_H_
#define SRC_MENU_PRINCIPAL_H_

class Opcion;
class Input;

#include <cstdint>

// 3 opciones en este menu
const uint8_t _n_opciones_principal = 3;

class Menu_Principal {
public:
	Menu_Principal(Input* _i_input);
	~Menu_Principal();

	void update(double _i_tiempo);
	
	uint8_t get_i_opcion();
	bool menu_opciones_abierto();
	uint8_t get_i_configuracion();
	uint8_t get_resolucion();
	uint8_t get_texturas();

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_PRINCIPAL_H_ */