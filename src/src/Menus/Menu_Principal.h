#ifndef SRC_MENU_PRINCIPAL_H_
#define SRC_MENU_PRINCIPAL_H_

class Opcion;
class Input;

#include <cstdint>

// 4 opciones en este menu
const uint8_t _n_opciones_principal = 4;

class Menu_Principal {
public:
	Menu_Principal(Input* _i_input);
	~Menu_Principal();

	void update(double _i_tiempo);

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_PRINCIPAL_H_ */