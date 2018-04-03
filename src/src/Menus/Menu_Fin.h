#ifndef SRC_MENU_FIN_H_
#define SRC_MENU_FIN_H_

class Opcion;
class Input;

#include <cstdint>

// 3 opciones en este menu
const uint8_t _n_opciones_fin = 2;

class Menu_Fin {
public:
	Menu_Fin(Input* _i_input);
	~Menu_Fin();

	void update(double _i_tiempo);

	void set_tiempo_fin();

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_FIN_H_ */