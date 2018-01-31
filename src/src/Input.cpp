#include "Input.h"

#include "Interfaz_Libs/Lib_Math.h"

#include <iostream>

Input::Input() {
	_teclas = new enum sf::Keyboard::Key[N_Inputs];
	_raton = new enum sf::Mouse::Button[N_Inputs];
	_posicion_raton = new Vector2(0,0);
	_vector_camara = new Vector2(0,0);

	_camara_con_teclado = false;
	_invertir_x = false;
	_invertir_y = true;

	_joystick_mover = new Vector2(0,0);
	_joystick_camara = new Vector2(0,0);

	_centrar_camara = false;

	_pausa = false;

	_hay_mando = false;
	_mando = new uint8_t[N_Inputs];
	_ejes = new sf::Joystick::Axis[N_Inputs];
	actualiza_mando();

	asignar_teclas_predefinidas();
}

Input::~Input() {
	delete [] _ejes;
	delete [] _mando;
	delete _joystick_mover;
	delete _joystick_camara;
	delete _vector_camara;
	delete _posicion_raton;
	delete [] _raton;
	delete [] _teclas;
}


// Asigna a los input las teclas predefinidas
void Input::asignar_teclas_predefinidas() {
	// ----------------- Inputs del teclado ---------------
	_teclas[Input_Arriba] = sf::Keyboard::W;
	_teclas[Input_Abajo] = sf::Keyboard::S;
	_teclas[Input_Izquierda] = sf::Keyboard::A;
	_teclas[Input_Derecha] = sf::Keyboard::D;

	_teclas[Input_Salto] = sf::Keyboard::Space;
	_teclas[Input_Interact] = sf::Keyboard::E;
	_teclas[Input_Dash] = sf::Keyboard::LShift;

	_teclas[Input_Ataque_Normal] = sf::Keyboard::Unknown;
	_teclas[Input_Ataque_Fuerte] = sf::Keyboard::Unknown;
	_teclas[Input_Ataque_Especial] = sf::Keyboard::Q;

	_teclas[Input_Arma_Izquierda] = sf::Keyboard::Num1;
	_teclas[Input_Arma_Derecha] = sf::Keyboard::Num2;

	_teclas[Input_Centrar_Camara] = sf::Keyboard::Unknown;

	_teclas[Input_Pausa] = sf::Keyboard::P;


	// ----------------- Inputs del raton ---------------
	_raton[Input_Arriba] = sf::Mouse::ButtonCount;
	_raton[Input_Abajo] = sf::Mouse::ButtonCount;
	_raton[Input_Izquierda] = sf::Mouse::ButtonCount;
	_raton[Input_Derecha] = sf::Mouse::ButtonCount;

	_raton[Input_Salto] = sf::Mouse::ButtonCount;
	_raton[Input_Interact] = sf::Mouse::ButtonCount;
	_raton[Input_Dash] = sf::Mouse::ButtonCount;

	_raton[Input_Ataque_Normal] = sf::Mouse::Left;
	_raton[Input_Ataque_Fuerte] = sf::Mouse::Right;
	_raton[Input_Ataque_Especial] = sf::Mouse::ButtonCount;

	_raton[Input_Arma_Izquierda] = sf::Mouse::ButtonCount;
	_raton[Input_Arma_Derecha] = sf::Mouse::ButtonCount;

	_raton[Input_Centrar_Camara] = sf::Mouse::Middle;

	_raton[Input_Pausa] = sf::Mouse::ButtonCount;


	// ----------------- Inputs de la camara ---------------
	_teclas[Input_Camara_Arriba] = sf::Keyboard::Up;
	_teclas[Input_Camara_Abajo] = sf::Keyboard::Down;
	_teclas[Input_Camara_Izquierda] = sf::Keyboard::Left;
	_teclas[Input_Camara_Derecha] = sf::Keyboard::Right;

	_raton[Input_Camara_Arriba] = sf::Mouse::ButtonCount;
	_raton[Input_Camara_Abajo] = sf::Mouse::ButtonCount;
	_raton[Input_Camara_Izquierda] = sf::Mouse::ButtonCount;
	_raton[Input_Camara_Derecha] = sf::Mouse::ButtonCount;
}


void Input::asignar_teclas_mando() {
	_mando[Input_Salto] = 0;			// A
	_mando[Input_Dash] = 1;				// B
	_mando[Input_Ataque_Normal] = 2;	// X
	_mando[Input_Ataque_Fuerte] = 3;	// Y
	_mando[Input_Ataque_Especial] = 4;	// LB

	_mando[Input_Interact] = 5;			// RB
	_mando[Input_Pausa] = 7;			// Start
	_mando[Input_Centrar_Camara] = 10;	// Boton Joystick Derecho

	_ejes[Input_Arma_Izquierda] = sf::Joystick::Z;
	_ejes[Input_Arma_Derecha] = sf::Joystick::R;

	_ejes[Input_Derecha] = sf::Joystick::X;
	_ejes[Input_Arriba] = sf::Joystick::Y;
	_ejes[Input_Camara_Derecha] = sf::Joystick::U;
	_ejes[Input_Camara_Arriba] = sf::Joystick::V;
}

// Activa la camara con teclado
void Input::activa_camara_teclado() {
	_camara_con_teclado = true;
	asignar_teclas_predefinidas();
	_posicion_raton->_x = 0;
	_posicion_raton->_y = 0;
}

// Desactiva la camara con teclado
void Input::desactiva_camara_teclado() {
	_camara_con_teclado = false;
	asignar_teclas_predefinidas();
}


// Invierte el eje X del la camara
void Input::invierte_eje_x() {

	_invertir_x = !_invertir_x;
}

// Invierte el eje Y del la camara
void Input::invierte_eje_y() {

	_invertir_y = !_invertir_y;
}

// Actualiza la informacion si hay o no mando
void Input::actualiza_mando() {
	sf::Joystick::update();

	// Comprueba si hay mando y si se puede usar
    if(sf::Joystick::isConnected(0)) {
    	if(_hay_mando == false) {// Si no habia mando
	    	_hay_mando = true;
			_botones_mando = sf::Joystick::getButtonCount(0);
			asignar_teclas_mando();
		}
		//std::cout << "Mando esta conectado, que tiene " << sf::Joystick::getButtonCount(0) << " botones\n";
    }
    else {
    	_hay_mando = false;
    	_botones_mando = 0;
		//std::cout << "Mando no esta conectado\n";
    }
}


// Devuelve si hay input de mover y los input de mover
bool Input::get_mover(uint16_t& _i_direccion) {
	_i_direccion = _direccion;

	return _mover;
}

// Recoge los inputs y almacena los valores
void Input::recibir_inputs() {
	if(_hay_mando) 
		recibir_inputs_mando();
	else
		recibir_inputs_teclado_raton();
}

// Recibe los inputs del mando
void Input::recibir_inputs_mando() {
	if(sf::Joystick::isButtonPressed(0, _mando[Input_Salto]) == true) {
		if(_ex_saltar == false){
			_saltar = true;
		}
		_ex_saltar = true;
	}
	else {
		_ex_saltar = false;
	}
	
	if(sf::Joystick::isButtonPressed(0, _mando[Input_Dash]) == true) {
		if(_ex_dash == false){
			_dash = true;
		}
		_ex_dash = true;
	}
	else {
		_ex_dash = false;
	}

	
	if(sf::Joystick::isButtonPressed(0, _mando[Input_Interact]) == true) {
		if(_ex_interactuar == false){
			_interactuar = true;
		}
		_ex_interactuar = true;
	}
	else {
		_ex_interactuar = false;
	}

	
	if(sf::Joystick::isButtonPressed(0, _mando[Input_Ataque_Normal]) == true) {
		if(_ex_ataque_normal == false){
			_ataque_normal = true;
		}
		_ex_ataque_normal = true;
	}
	else {
		_ex_ataque_normal = false;
	}

	
	if(sf::Joystick::isButtonPressed(0, _mando[Input_Ataque_Fuerte]) == true) {
		if(_ex_ataque_fuerte == false){
			_ataque_fuerte = true;
		}
		_ex_ataque_fuerte = true;
	}
	else {
		_ex_ataque_fuerte = false;
	}


	if(sf::Joystick::isButtonPressed(0, _mando[Input_Ataque_Especial]) == true) {
		if(_ex_ataque_especial == false){
			_ataque_especial = true;
		}
		_ex_ataque_especial = true;
	}
	else {
		_ex_ataque_especial = false;
	}


	if(sf::Joystick::getAxisPosition(0, _ejes[Input_Arma_Izquierda]) > 50) {
		if(_ex_cambia_a_izquierda == false){
			_cambia_a_izquierda = true;
		}
		_ex_cambia_a_izquierda = true;
	}
	else {
		_ex_cambia_a_izquierda = false;
	}


	if(sf::Joystick::getAxisPosition(0, _ejes[Input_Arma_Derecha]) > 50) {
		if(_ex_cambia_a_derecha == false){
			_cambia_a_derecha = true;
		}
		_ex_cambia_a_derecha = true;
	}
	else {
		_ex_cambia_a_derecha = false;
	}


	_joystick_mover->_x = sf::Joystick::getAxisPosition(0, _ejes[Input_Derecha]);
	_joystick_mover->_y = sf::Joystick::getAxisPosition(0, _ejes[Input_Arriba]);

	_joystick_camara->_x = sf::Joystick::getAxisPosition(0, _ejes[Input_Camara_Derecha]);
	_joystick_camara->_y = sf::Joystick::getAxisPosition(0, _ejes[Input_Camara_Arriba]);

	//_mando[Input_Usar_Arma] = 4;		// LB;
	_centrar_camara = sf::Joystick::isButtonPressed(0, _mando[Input_Centrar_Camara]);
	_pausa = sf::Joystick::isButtonPressed(0, _mando[Input_Pausa]);
}

// Recibe los inputs del teclado y el raton
void Input::recibir_inputs_teclado_raton() {
	bool _aux;

	if(_teclas[Input_Arriba] != sf::Keyboard::Unknown) 
		_arriba = sf::Keyboard::isKeyPressed(_teclas[Input_Arriba]);
	else 
		_arriba = sf::Mouse::isButtonPressed(_raton[Input_Arriba]);


	if(_teclas[Input_Abajo] != sf::Keyboard::Unknown) 
		_abajo = sf::Keyboard::isKeyPressed(_teclas[Input_Abajo]);
	else 
		_abajo = sf::Mouse::isButtonPressed(_raton[Input_Abajo]);


	if(_teclas[Input_Izquierda] != sf::Keyboard::Unknown) 
		_izquierda = sf::Keyboard::isKeyPressed(_teclas[Input_Izquierda]);
	else 
		_izquierda = sf::Mouse::isButtonPressed(_raton[Input_Izquierda]);


	if(_teclas[Input_Derecha] != sf::Keyboard::Unknown) 
		_derecha = sf::Keyboard::isKeyPressed(_teclas[Input_Derecha]);
	else 
		_derecha = sf::Mouse::isButtonPressed(_raton[Input_Derecha]);


	if(_teclas[Input_Salto] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Salto]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Salto]);
	if(_aux == true){
		if(_ex_saltar == false){
			_saltar = true;
		}
		_ex_saltar = true;
	}
	else {
		_ex_saltar = false;
	}


	if(_teclas[Input_Interact] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Interact]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Interact]);
	if(_aux == true){
		if(_ex_interactuar == false){
			_interactuar = true;
		}
		_ex_interactuar = true;
	}
	else {
		_ex_interactuar = false;
	}


	if(_teclas[Input_Dash] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Dash]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Dash]);
	if(_aux == true){
		if(_ex_dash == false){
			_dash = true;
		}
		_ex_dash = true;
	}
	else {
		_ex_dash = false;
	}


	if(_teclas[Input_Ataque_Normal] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Ataque_Normal]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Ataque_Normal]);
	if(_aux == true) {
		if(_ex_ataque_normal == false){
			_ataque_normal = true;
		}
		_ex_ataque_normal = true;
	}
	else {
		_ex_ataque_normal = false;
	}


	if(_teclas[Input_Ataque_Fuerte] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Ataque_Fuerte]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Ataque_Fuerte]);
	if(_aux == true) {
		if(_ex_ataque_fuerte == false){
			_ataque_fuerte = true;
		}
		_ex_ataque_fuerte = true;
	}
	else {
		_ex_ataque_fuerte = false;
	}


	if(_teclas[Input_Ataque_Especial] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Ataque_Especial]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Ataque_Especial]);
	if(_aux == true) {
		if(_ex_ataque_especial == false){
			_ataque_especial = true;
		}
		_ex_ataque_especial = true;
	}
	else {
		_ex_ataque_especial = false;
	}


	if(_teclas[Input_Arma_Izquierda] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Arma_Izquierda]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Arma_Izquierda]);
	if(_aux == true) {
		if(_ex_cambia_a_izquierda == false){
			_cambia_a_izquierda = true;
		}
		_ex_cambia_a_izquierda = true;
	}
	else {
		_ex_cambia_a_izquierda = false;
	}


	if(_teclas[Input_Arma_Derecha] != sf::Keyboard::Unknown) 
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Arma_Derecha]);
	else 
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Arma_Derecha]);
	if(_aux == true) {
		if(_ex_cambia_a_derecha == false){
			_cambia_a_derecha = true;
		}
		_ex_cambia_a_derecha = true;
	}
	else {
		_ex_cambia_a_derecha = false;
	}

	if(_camara_con_teclado)
		recibir_inputs_camara();


	if(_teclas[Input_Centrar_Camara] != sf::Keyboard::Unknown)
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Centrar_Camara]);
	else
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Centrar_Camara]);
	if(_aux == true) {
		if(_ex_centrar_camara == false){
			_centrar_camara = true;
		}
		_ex_centrar_camara = true;
	}
	else {
		_ex_centrar_camara = false;
	}


	if(_teclas[Input_Pausa] != sf::Keyboard::Unknown)
		_aux = sf::Keyboard::isKeyPressed(_teclas[Input_Pausa]);
	else
		_aux = sf::Mouse::isButtonPressed(_raton[Input_Pausa]);
	if(_aux == true) {
		if(_ex_pausa == false){
			_pausa = true;
		}
		_ex_pausa = true;
	}
	else {
		_ex_pausa = false;
	}
}

// Recibe y guarda los inputs de la camara
void Input::recibir_inputs_camara() {
	if(_teclas[Input_Camara_Arriba] != sf::Keyboard::Unknown) 
		_arriba_camara = sf::Keyboard::isKeyPressed(_teclas[Input_Camara_Arriba]);
	else 
		_arriba_camara = sf::Mouse::isButtonPressed(_raton[Input_Camara_Arriba]);


	if(_teclas[Input_Abajo] != sf::Keyboard::Unknown) 
		_abajo_camara = sf::Keyboard::isKeyPressed(_teclas[Input_Camara_Abajo]);
	else 
		_abajo_camara = sf::Mouse::isButtonPressed(_raton[Input_Camara_Abajo]);


	if(_teclas[Input_Camara_Izquierda] != sf::Keyboard::Unknown) 
		_izquierda_camara = sf::Keyboard::isKeyPressed(_teclas[Input_Camara_Izquierda]);
	else 
		_izquierda_camara = sf::Mouse::isButtonPressed(_raton[Input_Camara_Izquierda]);


	if(_teclas[Input_Camara_Derecha] != sf::Keyboard::Unknown) 
		_derecha_camara = sf::Keyboard::isKeyPressed(_teclas[Input_Camara_Derecha]);
	else 
		_derecha_camara = sf::Mouse::isButtonPressed(_raton[Input_Camara_Derecha]);
}


// Procesa los inputs para darlos al jugador
void Input::procesar_inputs() {
	procesa_direccion();
	procesa_camara();

	_ataque = _ataque_normal || _ataque_fuerte || _ataque_especial;
	_cambia_arma = _cambia_a_izquierda || _cambia_a_derecha;

	//pinta_couts_inputs();
}


// Procesa los input de direccion para sacar la direccion de movimiento del jugador
void Input::procesa_direccion() {
	if(_hay_mando)
		procesa_direccion_mando();
	else
		procesa_direccion_teclado();
}

void Input::procesa_direccion_mando() {
	if(std::abs(_joystick_mover->_x) > 20 || std::abs(_joystick_mover->_y) > 20) {
		_mover = true;
        _direccion = lib_math_angulo_2_puntos(_joystick_mover->_y, -_joystick_mover->_x, 0, 0);
    }
    else {
    	_mover = false;
    }
}

void Input::procesa_direccion_teclado(){
	if(_arriba || _abajo || _izquierda || _derecha) {
		_mover = true;
	
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
}


// Procesa los input de camara para sacar la direccion de movimiento de camara
void Input::procesa_camara() {
	if(_hay_mando)
		procesa_camara_mando();
	else if(_camara_con_teclado) 
		procesa_camara_teclado();
	else
		procesa_camara_raton();

	if(std::abs(_vector_camara->_x)<0.000001) _vector_camara->_x=0;
	if(std::abs(_vector_camara->_y)<0.000001) _vector_camara->_y=0;

	if(_invertir_x && _vector_camara->_x != 0) _vector_camara->_x *= -1;
	if(_invertir_y && _vector_camara->_y != 0) _vector_camara->_y *= -1;
	
	if(_centrar_camara) {
		_mover_camara = false;
	}

	/*
	if(_mover_camara) {
		std::cout << "Angulo = " << _direccion_camara  << "\n";
		if(!_hay_mando && !_camara_con_teclado)
			std::cout << "Posicion del raton = (" << _posicion_raton->_x << "," << _posicion_raton->_y << ")\n";
		std::cout << "Angulo de la camara = (" << _vector_camara->_x << "," << _vector_camara->_y << ")\n";
	}
	*/
}

void Input::procesa_camara_mando() {
	if(std::abs(_joystick_camara->_x) > 20 || std::abs(_joystick_camara->_y) > 20) {
		_mover_camara = true;
        /*_direccion_camara = lib_math_angulo_2_puntos(_joystick_camara->_y, -_joystick_camara->_x, 0, 0);

		_vector_camara->_y = cos(_direccion_camara*std::acos(-1)/180);
	    _vector_camara->_x = sin(_direccion_camara*std::acos(-1)/180);*/

	    _vector_camara->_x = _joystick_camara->_x/100;
	    _vector_camara->_y = -_joystick_camara->_y/100;
    }
    else {
    	_mover_camara = false;
    }
}

void Input::procesa_camara_raton() {
	sf::Vector2i _vector = sf::Mouse::getPosition();

	if(_vector.x != _posicion_raton->_x || _vector.y != _posicion_raton->_y) {
		_mover_camara = true;

		_direccion_camara = lib_math_angulo_2_puntos(_vector.y, _posicion_raton->_x, _posicion_raton->_y, _vector.x);

		_posicion_raton->_x = _vector.x;
		_posicion_raton->_y = _vector.y;

		_vector_camara->_y = cos(_direccion_camara*std::acos(-1)/180);
	    _vector_camara->_x = sin(_direccion_camara*std::acos(-1)/180);
	}
}

void Input::procesa_camara_teclado() {
    float aux = sin(45*std::acos(-1)/180);

	if(_arriba_camara || _abajo_camara || _izquierda_camara || _derecha_camara) {
		_mover_camara = true;

	    if(_arriba_camara){
	        if(_derecha_camara){
	            _direccion_camara = 45;
	    		_vector_camara->_x = aux;
	            _vector_camara->_y = aux;

	        }
	        else if(_izquierda_camara){
	            _direccion_camara = 315;
	    		_vector_camara->_x = -aux;
	            _vector_camara->_y = aux;
	        }
	        else {
	            _direccion_camara = 0;
	    		_vector_camara->_x = 0;
	            _vector_camara->_y = 1;
	        }
	    }

	    else if(_abajo_camara){
	        if(_derecha_camara){
	            _direccion_camara = 135;
	    		_vector_camara->_x = aux;
	            _vector_camara->_y = -aux;
	        }
	        else if(_izquierda_camara){
	            _direccion_camara = 225;
	    		_vector_camara->_x = -aux;
	            _vector_camara->_y = -aux;
	        }
	        else {
	            _direccion_camara = 180;
	    		_vector_camara->_x = 0;
	            _vector_camara->_y = -1;
	        }
	    } 

	    else if(_derecha_camara){
	        _direccion_camara = 90;
    		_vector_camara->_x = 1;
            _vector_camara->_y = 0;
	    }

	    else if(_izquierda_camara){
	        _direccion_camara = 270;
    		_vector_camara->_x = -1;
            _vector_camara->_y = 0;
	    }
	}
}


// Reinicia los inputs a su valor inicial
void Input::reiniciar_inputs() {
	_arriba = false;
    _abajo = false;
    _izquierda = false;
    _derecha = false;
    _mover = false;

    _saltar = false;
    _interactuar = false;
    _dash = false;

    _ataque = false;
    _ataque_normal = false;
    _ataque_fuerte = false;
    _ataque_especial = false;

    _cambia_arma = false;
    _cambia_a_izquierda = false;
    _cambia_a_derecha = false;

    _mover_camara = false;
    _centrar_camara = false;

	_pausa = false;

	actualiza_mando();
}



// CONTROL Y REASIGNACION DE TECLAS

// Asigna todas las teclas de entrada
// Seguramente se borre una vez se tenga un menu y forma de acceder a ello
// Haciendo publico asigna_tecla() y llamando con los distintos enums
void Input::asignar_teclas_entrada() {
	
	asigna_tecla(Input_Arriba);
}


// Se le pasa por parametro la tecla a reasignar
// Se recoge la nueva asignacion de la tecla
// En caso de que otra tecla tuviera esa asignacion, se reasigna
void Input::asigna_tecla(enum Enum_Inputs _input) {
	enum sf::Keyboard::Key _tecla_aux;
	enum sf::Mouse::Button _raton_aux;
	enum sf::Keyboard::Key _tecla_antigua = _teclas[_input];
	enum sf::Mouse::Button _raton_antiguo = _raton[_input];

	//pinta_inputs();

	bool _es_key = lee_asignacion_input(_tecla_aux, _raton_aux);

	if(_es_key && _tecla_aux != sf::Keyboard::Unknown || _es_key == false) {
		enum Enum_Inputs _input_aux;

		_teclas[_input] = _tecla_aux;
		_raton[_input] = _raton_aux;

		if(_es_key)
			_input_aux = comprueba_tecla(_input);
		else
			_input_aux = comprueba_raton(_input);

		// Si esa tecla estaba asignada a otra, se cambia una por otra (Izq era A, Der era D, se pone D en Izq y A pasa a ser Der)
		if(_input_aux != Ninguno) {
			_teclas[_input_aux] = _tecla_antigua;
			_raton[_input_aux] = _raton_antiguo;
		}
	}

	//pinta_inputs();
}


// Comprueba si la tecla de un input se encuentra asignado a otro input y lo devuelve
enum Enum_Inputs Input::comprueba_tecla(enum Enum_Inputs _tecla_a_comprobar) {
	for(uint8_t _cont=0; _cont<N_Inputs; _cont++) {
		if(_teclas[_cont] == _teclas[_tecla_a_comprobar] && _cont!=_tecla_a_comprobar) {
			return static_cast<Enum_Inputs>(_cont);
		}
	}
	return Ninguno;
}

// Comprueba si el boton del raton de un input se encuentra asignado a otro input y lo devuelve
enum Enum_Inputs Input::comprueba_raton(enum Enum_Inputs _raton_a_comprobar) {
	for(uint8_t _cont=0; _cont<N_Inputs; _cont++) {
		if(_raton[_cont] == _raton[_raton_a_comprobar] && _cont!=_raton_a_comprobar) {
			return static_cast<Enum_Inputs>(_cont);
		}
	}
	return Ninguno;
}


// Lee constanemente del teclado hasta que se pulsa una tecla que se devuelve
// Las teclas Esc y BackSpace (borrar) devuelven unknown para cancelar asignacion
bool Input::lee_asignacion_input(enum sf::Keyboard::Key& _tecla, enum sf::Mouse::Button& _boton) {
	while(true) {
		// Salida de la asignacion
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {_tecla = sf::Keyboard::Unknown; _boton = sf::Mouse::ButtonCount; return true; }

		// -------------- KEYBOARD --------------
		// Letras
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  			_tecla = sf::Keyboard::A; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {  			_tecla = sf::Keyboard::B; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {  			_tecla = sf::Keyboard::C; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  			_tecla = sf::Keyboard::D; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {  			_tecla = sf::Keyboard::E; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {  			_tecla = sf::Keyboard::F; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {  			_tecla = sf::Keyboard::G; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {  			_tecla = sf::Keyboard::H; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {  			_tecla = sf::Keyboard::I; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {  			_tecla = sf::Keyboard::J; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {  			_tecla = sf::Keyboard::K; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {  			_tecla = sf::Keyboard::L; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {  			_tecla = sf::Keyboard::M; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {  			_tecla = sf::Keyboard::N; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {  			_tecla = sf::Keyboard::O; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {  			_tecla = sf::Keyboard::P; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {  			_tecla = sf::Keyboard::Q; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {  			_tecla = sf::Keyboard::R; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  			_tecla = sf::Keyboard::S; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {  			_tecla = sf::Keyboard::T; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {  			_tecla = sf::Keyboard::U; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {  			_tecla = sf::Keyboard::V; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  			_tecla = sf::Keyboard::W; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {  			_tecla = sf::Keyboard::X; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {  			_tecla = sf::Keyboard::Y; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {  			_tecla = sf::Keyboard::Z; _boton = sf::Mouse::ButtonCount; return true; }

		// Flechas
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {  		_tecla = sf::Keyboard::Left; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  		_tecla = sf::Keyboard::Right; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  		_tecla = sf::Keyboard::Up; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {  		_tecla = sf::Keyboard::Down; _boton = sf::Mouse::ButtonCount; return true; }

		// Numeros superiores
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {  		_tecla = sf::Keyboard::Num0; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {  		_tecla = sf::Keyboard::Num1; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {  		_tecla = sf::Keyboard::Num2; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {  		_tecla = sf::Keyboard::Num3; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {  		_tecla = sf::Keyboard::Num4; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {  		_tecla = sf::Keyboard::Num5; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {  		_tecla = sf::Keyboard::Num6; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {  		_tecla = sf::Keyboard::Num7; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {  		_tecla = sf::Keyboard::Num8; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {  		_tecla = sf::Keyboard::Num9; _boton = sf::Mouse::ButtonCount; return true; }

		// Numeros del pad derecho
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {  	_tecla = sf::Keyboard::Numpad0; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {  	_tecla = sf::Keyboard::Numpad1; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {  	_tecla = sf::Keyboard::Numpad2; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {  	_tecla = sf::Keyboard::Numpad3; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {  	_tecla = sf::Keyboard::Numpad4; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {  	_tecla = sf::Keyboard::Numpad5; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {  	_tecla = sf::Keyboard::Numpad6; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {  	_tecla = sf::Keyboard::Numpad7; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {  	_tecla = sf::Keyboard::Numpad8; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {  	_tecla = sf::Keyboard::Numpad9; _boton = sf::Mouse::ButtonCount; return true; }

		// Otras teclas
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  		_tecla = sf::Keyboard::Space; _boton = sf::Mouse::ButtonCount; return true; }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {  	_tecla = sf::Keyboard::LShift; _boton = sf::Mouse::ButtonCount; return true; }


		
		// -------------- MOUSE --------------
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  			_boton = sf::Mouse::Left; _tecla = sf::Keyboard::Unknown; return false; }
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {  		_boton = sf::Mouse::Right; _tecla = sf::Keyboard::Unknown; return false; }
		if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {  		_boton = sf::Mouse::Middle; _tecla = sf::Keyboard::Unknown; return false; }
		if(sf::Mouse::isButtonPressed(sf::Mouse::XButton1)) {  		_boton = sf::Mouse::XButton1; _tecla = sf::Keyboard::Unknown; return false; }
		if(sf::Mouse::isButtonPressed(sf::Mouse::XButton2)) {  		_boton = sf::Mouse::XButton2; _tecla = sf::Keyboard::Unknown; return false; }
	}
}



// Pinta los couts de inputs recibidos
void Input::pinta_couts_inputs() {
	if(_mover) std::cout << "Se mueve en la direccion " << _direccion << "\n";
	if(_saltar) std::cout << "Se realiza un salto\n";
	if(_interactuar) std::cout << "Se interactua\n";
	if(_dash) std::cout << "Se realiza un dash\n";
	if(_ataque) std::cout << "Se realiza un ataque\n";
	if(_ataque_normal) std::cout << "Se realiza un ataque normal\n";
	if(_ataque_fuerte) std::cout << "Se realiza un ataque fuerte\n";
	if(_ataque_especial) std::cout << "Se realiza un ataque especial\n";
	if(_cambia_arma) std::cout << "Cambia de arma\n";
	if(_cambia_a_derecha) std::cout << "Cambia a arma derecha\n";
	if(_cambia_a_izquierda) std::cout << "Cambia a arma izquierda\n";

	//std::cout << "\n";
}

// Pinta las asignaciones de inputs
void Input::pinta_inputs() {
	std::cout << "\nTeclado:\n";
	for(uint8_t _cont=0; _cont<N_Inputs; _cont++) {
		std::cout << "[" << _teclas[_cont] << "]";
	}
	std::cout << "\nRaton:\n";
	for(uint8_t _cont=0; _cont<N_Inputs; _cont++) {
		std::cout << "[" << _raton[_cont] << "]";
	}
	std::cout << "\n\n";
}