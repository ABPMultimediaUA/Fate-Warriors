#include "Input.h"

#include <iostream>

Input::Input() {
	_teclas = new enum sf::Keyboard::Key[N_Teclas];

	asignar_teclas_predefinidas();
}

Input::~Input() {
	delete [] _teclas;
}


void Input::recibir_inputs() {
	_arriba = sf::Keyboard::isKeyPressed(_teclas[Tecla_Arriba]);
    _abajo = sf::Keyboard::isKeyPressed(_teclas[Tecla_Abajo]);
    _izquierda = sf::Keyboard::isKeyPressed(_teclas[Tecla_Izquierda]);
    _derecha = sf::Keyboard::isKeyPressed(_teclas[Tecla_Derecha]);

    if(_arriba) std::cout << "Ha pulsado arriba\n";
    if(_abajo) std::cout << "Ha pulsado abajo\n";
    if(_izquierda) std::cout << "Ha pulsado izquierda\n";
    if(_derecha) std::cout << "Ha pulsado derecha\n";
}


void Input::procesar_inputs() {
	procesa_direccion();

	if(_mover) std::cout << "Se mueve en la direccion " << _direccion << "\n";

	reiniciar_inputs();
}


void Input::asignar_teclas_predefinidas() {
	_teclas[Tecla_Arriba] = sf::Keyboard::W;
	_teclas[Tecla_Abajo] = sf::Keyboard::S;
	_teclas[Tecla_Izquierda] = sf::Keyboard::A;
	_teclas[Tecla_Derecha] = sf::Keyboard::D;
}




void Input::procesa_direccion() {
	if(_arriba || _abajo || _izquierda || _derecha) {
		_mover = true;
	}

	
    if(_arriba){
        if(_derecha){
            _direccion = 45;
        }
        else if(_izquierda){
            _direccion = 315;
        }
        else {
            _direccion = 0;
        }
    }

    else if(_abajo){
        if(_derecha){
            _direccion = 135;
        }
        else if(_izquierda){
            _direccion = 225;
        }
        else {
            _direccion = 180;
        }
    } 

    else if(_derecha){
        _direccion = 90;
    }

    else if(_izquierda){
        _direccion = 270;
    }
}


void Input::reiniciar_inputs() {
	_arriba = false;
    _abajo = false;
    _izquierda = false;
    _derecha = false;
    _mover = false;
}




// CONTROL Y REASIGNACION DE TECLAS

// Asigna todas las teclas de entrada
void Input::asignar_teclas_entrada() {
	
	asigna_tecla(Tecla_Arriba);
}


// Se le pasa por parametro la tecla a reasignar
// Se recoge la nueva asignacion de la tecla
// En caso de que otra tecla tuviera esa asignacion, se reasigna
void Input::asigna_tecla(enum Enum_Teclas _tecla) {
	enum sf::Keyboard::Key _tecla_aux = _teclas[_tecla];

	_teclas[_tecla] = lee_tecla();	

	if(_teclas[_tecla] != sf::Keyboard::Unknown) {
		enum Enum_Teclas _tecla_aux_2;
		//std::cout << "Se asigna la tecla " << _teclas[_tecla] << " a la tecla Arriba\n";
		
		_tecla_aux_2 = comprueba_tecla(_tecla);

		// Si esa tecla estaba asignada a otra, se cambia una por otra (Izq era A, Der era D, se pone D en Izq y A pasa a ser Der)
		if(_tecla_aux_2 != Ninguna) {
			_teclas[_tecla_aux_2] = _tecla_aux;
			std::cout << "Se cambia la tecla " << _teclas[_tecla_aux_2] << " a la tecla " << _tecla_aux_2 << "\n";
		}
	}
	else{
		_teclas[_tecla] = _tecla_aux;
	}
}


// Comprueba si la asignacion de una tecla se encuentra asignada a otra tecla y la devuelve
enum Enum_Teclas Input::comprueba_tecla(enum Enum_Teclas _tecla_a_comprobar) {
	for(uint8_t _cont=0; _cont<N_Teclas; _cont++) {
		if(_teclas[_cont] == _teclas[_tecla_a_comprobar] && _cont!=_tecla_a_comprobar) {
			return static_cast<Enum_Teclas>(_cont);
		}
	}
	return Ninguna;
}


// Lee constanemente del teclado hasta que se pulsa una tecla que se devuelve
// Las teclas Esc y BackSpace (borrar) devuelven unknown para cancelar asignacion
enum sf::Keyboard::Key Input::lee_tecla() {
	while(true) {
		// Salida de la asignacion
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) 	return sf::Keyboard::Unknown;

		// Letras
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 		return sf::Keyboard::A;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) 		return sf::Keyboard::B;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) 		return sf::Keyboard::C;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 		return sf::Keyboard::D;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) 		return sf::Keyboard::E;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) 		return sf::Keyboard::F;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 		return sf::Keyboard::G;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) 		return sf::Keyboard::H;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) 		return sf::Keyboard::I;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) 		return sf::Keyboard::J;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) 		return sf::Keyboard::K;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 		return sf::Keyboard::L;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) 		return sf::Keyboard::M;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) 		return sf::Keyboard::N;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) 		return sf::Keyboard::O;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) 		return sf::Keyboard::P;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 		return sf::Keyboard::Q;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 		return sf::Keyboard::R;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 		return sf::Keyboard::S;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) 		return sf::Keyboard::T;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) 		return sf::Keyboard::U;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) 		return sf::Keyboard::V;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 		return sf::Keyboard::W;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) 		return sf::Keyboard::X;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) 		return sf::Keyboard::Y;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) 		return sf::Keyboard::Z;

		// Flechas
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 		return sf::Keyboard::Left;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 	return sf::Keyboard::Right;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 		return sf::Keyboard::Up;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 		return sf::Keyboard::Down;

		// Numeros superiores
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) 		return sf::Keyboard::Num0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) 		return sf::Keyboard::Num1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) 		return sf::Keyboard::Num2;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) 		return sf::Keyboard::Num3;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) 		return sf::Keyboard::Num4;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) 		return sf::Keyboard::Num5;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) 		return sf::Keyboard::Num6;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) 		return sf::Keyboard::Num7;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) 		return sf::Keyboard::Num8;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) 		return sf::Keyboard::Num9;

		// Numeros del pad derecho
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) 		return sf::Keyboard::Numpad0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) 		return sf::Keyboard::Numpad1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) 		return sf::Keyboard::Numpad2;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) 		return sf::Keyboard::Numpad3;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) 		return sf::Keyboard::Numpad4;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) 		return sf::Keyboard::Numpad5;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) 		return sf::Keyboard::Numpad6;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) 		return sf::Keyboard::Numpad7;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) 		return sf::Keyboard::Numpad8;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) 		return sf::Keyboard::Numpad9;

		// Otras teclas
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 	return sf::Keyboard::Space;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) 	return sf::Keyboard::LShift;
	}
}