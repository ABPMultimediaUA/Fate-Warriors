#ifndef SRC_MENU_CONFIGURACION_H_
#define SRC_MENU_CONFIGURACION_H_

class Opcion;
class Input;

#include <cstdint>

// 6 opciones en este menu
const uint8_t _n_opciones_configuracion = 6;

class Menu_Configuracion {
public:
	Menu_Configuracion(Input* _i_input);
	~Menu_Configuracion();

	void update(double _i_tiempo);

	void actualiza();	// Actualiza los valores de las opciones

	uint8_t get_i_configuracion();	// Devuelve la opción actual

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;

	Input* _input;

	void pinta_estado();
};

#endif /* SRC_MENU_CONFIGURACION_H_ */