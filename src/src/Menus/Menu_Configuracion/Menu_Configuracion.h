#ifndef SRC_MENU_CONFIGURACION_H_
#define SRC_MENU_CONFIGURACION_H_

class Opcion;
class Input;

#include <cstdint>

// 5 opciones en este menu
const uint8_t _n_opciones_principal = 6;

class Menu_Configuracion {
public:
	Menu_Configuracion(Input* _i_input);
	~Menu_Configuracion();

	void update(double _i_tiempo);

	void actualiza();	// Actualiza los valores de las opciones

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_CONFIGURACION_H_ */