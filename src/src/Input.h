#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include "SFML/Graphics.hpp"

#include "Utilidades/Vector.h"

#include <cstdint>

enum Enum_Inputs {
	Input_Arriba,
	Input_Abajo,
	Input_Izquierda,
	Input_Derecha,
	Input_Salto,
	Input_Interact,
	Input_Dash,
	Input_Ataque_Normal,
	Input_Ataque_Fuerte,
	Input_Camara_Arriba,
	Input_Camara_Abajo,
	Input_Camara_Izquierda,
	Input_Camara_Derecha,
	N_Inputs,
	Ninguno
};

class Input {
public:
	Input();
	~Input();

	void recibir_inputs();		// Recibir los inputs 								->	Ejecutar todas las veces que sea posible
	void procesar_inputs();		// Procesa los inputs recibidos						->	Ejecutar 1 vez antes de que player pueda usarlos
	void reiniciar_inputs();	// Reiniciar los inputs para volver a recibirlos 	->	Ejecutar 1 vez despues de usarlos

	void asignar_teclas_predefinidas();
	void asignar_teclas_entrada();

	void activa_camara_teclado();
	void desactiva_camara_teclado();

	void invierte_eje_x();
	void invierte_eje_y();

	bool get_mover(uint16_t& _i_direccion);
	bool get_saltar();
	bool get_interactuar();
	bool get_dash();
	bool get_atacar(bool& _normal, bool& _fuerte);


private:
	// Control de las teclas
	bool _arriba;
	bool _abajo;
	bool _izquierda;
	bool _derecha;

	bool _arriba_camara;
	bool _abajo_camara;
	bool _izquierda_camara;
	bool _derecha_camara;

	bool _camara_con_teclado;	// Indica si se controla la camara con el teclado
	bool _invertir_x;			// Invierte el eje X de la camara
	bool _invertir_y;			// Invierte el eje Y de la camara



	// Datos de input
	bool _mover;				// Indica si se ha pulsado un input para moverse
	uint16_t _direccion;		// Indica la direccion de movimiento que se ha recibido

	bool _saltar;				// Indica si se ha pulsado el input para realizar un salto
	bool _interactuar;			// Indica si se ha pulsado el input para interactuar
	bool _dash;					// Indica si se ha pulsado el input para realizar un dash

	bool _ataque;				// Indica si se ha pulsado un input para realizar un ataque
	bool _ataque_normal;		// Indica si se ha pulsado el input para realizar un ataque normal
	bool _ataque_fuerte;		// Indica si se ha pulsado el input para realizar un ataque fuerte

	Vector2* _posicion_raton;	// Posicion actual del raton en la pantalla
	bool _mover_camara;			// Indica si se mueve la camara o no
	uint16_t _direccion_camara;	// Angulo de direccion de movimiento de la camara
	Vector2* _vector_camara;	// Vector normalizado de direccion para el movimiento de la camara


	// Teclas de control
	enum sf::Keyboard::Key* _teclas;
	enum sf::Mouse::Button* _raton;


	// Funciones de control
	void procesa_direccion();

	void recibir_inputs_camara();

	void procesa_camara();
	void procesa_camara_raton();
	void procesa_camara_teclado();


	// Funciones de asignacion de teclas
	void asigna_tecla(enum Enum_Inputs _tecla);
	enum Enum_Inputs comprueba_tecla(enum Enum_Inputs _tecla_a_comprobar);
	enum Enum_Inputs comprueba_raton(enum Enum_Inputs _raton_a_comprobar);
	bool lee_asignacion_input(enum sf::Keyboard::Key& _tecla, enum sf::Mouse::Button& _boton);


	// Funciones de debug
	void pinta_couts_inputs();
	void pinta_inputs();
};

#endif /* SRC_INPUT_H_ */