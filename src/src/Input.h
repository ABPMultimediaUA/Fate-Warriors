#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include "SFML/Graphics.hpp"

#include <cstdint>

enum Enum_Teclas {
	Tecla_Arriba,
	Tecla_Abajo,
	Tecla_Izquierda,
	Tecla_Derecha,
	N_Teclas,
	Ninguna
};

class Input {
public:
	Input();
	~Input();

	void recibir_inputs();
	void procesar_inputs();

	void asignar_teclas_predefinidas();
	void asignar_teclas_entrada();

private:
	// Control de las teclas
	bool _arriba;
	bool _abajo;
	bool _izquierda;
	bool _derecha;

	// Datos de input
	bool _mover;
	uint16_t _direccion;

	// Teclas de control
	enum sf::Keyboard::Key* _teclas;

	// Funciones de control
	void procesa_direccion();
	void reiniciar_inputs();


	// Funciones de asignacion de teclas
	void asigna_tecla(enum Enum_Teclas _tecla);
	enum Enum_Teclas comprueba_tecla(enum Enum_Teclas _tecla_a_comprobar);
	enum sf::Keyboard::Key lee_tecla();

};

#endif /* SRC_INPUT_H_ */