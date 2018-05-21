#ifndef SRC_OPCION_H_
#define SRC_OPCION_H_

class Input;
class Interfaz_sonido;

#include <cstdint>

// Opcion seleccionable en los menus
// Tiene su propio update, desde el que se puede llamar al cambio de estados de Game

class Opcion {
public:
	Opcion(Input* _i_input);
	virtual ~Opcion();

	Opcion* update(double _i_tiempo, Opcion* _this);								// Update publico
	virtual Opcion* comprueba_cambio_opcion(Opcion* _this);							// Comprueba si hay que pasar a la opcion siguiente

	void set_opciones(Opcion* _i_opcion_anterior, Opcion* _i_opcion_siguiente);		// Agrega las opciones anterior y siguiente
	void set_tiempo(double _t);	// Pone el tiempo de cambio a cierto tiempo

	// Funciones para las clases hijas
	virtual void actualiza_valores();
	virtual bool get_dentro();
	virtual uint8_t get_i_configuracion();
	virtual void agrega_submenus(Opcion* _i_opcion_izq, Opcion* _i_opcion_der) ;
	virtual uint8_t get_resolucion();
	virtual uint8_t get_texturas();

protected:
	Opcion *_opcion_anterior;		// Opcion anterior (arriba) en el menu
	Opcion *_opcion_siguiente;		// Opcion siguiente (debajo) en el menu1

	Input *_input;					// Input para recoger los inputs

	virtual Opcion* update_opcion(double _i_tiempo, Opcion* _this) = 0;	// Funcion virtual pura de update propio de cada opcion

	static uint32_t _tiempo_cambio;						// Tiempo (momento) en el que se cambio entre opcinoes

	Interfaz_sonido* _sonido;

private: 
	void set_opcion_anterior(Opcion* _i_opcion);		// Set opcion anterior
	void set_opcion_siguiente(Opcion* _i_opcion);		// Set opcion siguiente
};

#endif /* SRC_OPCION_H_ */