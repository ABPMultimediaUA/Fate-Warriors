#include "Interpolacion.h"

Interpolacion::Interpolacion(Vector3 _i_posicion_inicial) {
	_posicion_actual = new Vector3(_i_posicion_inicial);
	_posicion_anterior = new Vector3(_i_posicion_inicial);

	_direccion_actual = 0;
	_direccion_anterior = 0;
}

Interpolacion::~Interpolacion() {
	delete _posicion_anterior;
	delete _posicion_actual;
}


// Hace de posicion anterior la posicion actual
// Hace la posicion actual la posicion que llega por parametro
void Interpolacion::actualiza_posicion(Vector3 _i_posicion_actual) {
	// POSICION_ANTERIOR = POSICION_ACTUAL
	_posicion_anterior->_x = _posicion_actual->_x;
	_posicion_anterior->_y = _posicion_actual->_y;
	_posicion_anterior->_z = _posicion_actual->_z;


	// POSICION_ACTUAL = i_POSICION_ACTUAL
	_posicion_actual->_x = _i_posicion_actual._x;
	_posicion_actual->_y = _i_posicion_actual._y;
	_posicion_actual->_z = _i_posicion_actual._z;
}


// Interpola la posicion para un % de render y lo devuelve como un Vector3
Vector3 Interpolacion::interpola_posicion(float _i_interpolacion){
    float _x_interpolada = _posicion_anterior->_x * (1 -_i_interpolacion) + _posicion_actual->_x * _i_interpolacion;
    float _y_interpolada = _posicion_anterior->_y * (1 -_i_interpolacion) + _posicion_actual->_y * _i_interpolacion;
    float _z_interpolada = _posicion_anterior->_z * (1 -_i_interpolacion) + _posicion_actual->_z * _i_interpolacion;

    return Vector3(_x_interpolada, _y_interpolada, _z_interpolada);
}


// Hace de direccion anterior la direccion actual
// Hace la direccion actual la direccion que llega por parametro
void Interpolacion::actualiza_direccion(int16_t _i_direccion_actual) {

	// direccion_ANTERIOR = direccion_ACTUAL
	_direccion_anterior = _direccion_actual;

	// direccion_ACTUAL = i_direccion_ACTUAL
	_direccion_actual = _i_direccion_actual;

	//std::cout << "Direccion actual " << (int)_direccion_actual << "\n";
	//std::cout << "Direccion anterior " << (int)_direccion_anterior << "\n";

	// En caso de ser una variacion de mas de 180º, pega una vuelta entera para girar de la forma mas eficiente
	int16_t _diferencia = _direccion_actual - _direccion_anterior;
	if(_diferencia > 180) {
		_direccion_anterior += 360;
		//std::cout << "Direccion anterior modificada " << (int)_direccion_anterior << "\n\n";
	}
	else if(_diferencia < -180) {
		_direccion_anterior -= 360;
		//std::cout << "Direccion anterior modificada " << (int)_direccion_anterior << "\n\n";
	}

	_cambio_direccion = true;
}


// Interpola la direccion para un % de render y lo devuelve como un uint16_t
int16_t Interpolacion::interpola_direccion(float _i_interpolacion){
    int16_t _direccion_interpolada = _direccion_anterior * (1 -_i_interpolacion) + _direccion_actual * _i_interpolacion;

    return _direccion_interpolada;
}
