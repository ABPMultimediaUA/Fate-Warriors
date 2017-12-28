#include "Interpolacion.h"

Interpolacion::Interpolacion(Vector3 _i_posicion_inicial) {
	_posicion_actual = new Vector3(_i_posicion_inicial);
	_posicion_anterior = new Vector3(_i_posicion_inicial);
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
    float _x_interpolada= _posicion_anterior->_x * (1 -_i_interpolacion) + _posicion_actual->_x * _i_interpolacion;
    float _y_interpolada= _posicion_anterior->_y * (1 -_i_interpolacion) + _posicion_actual->_y * _i_interpolacion;
    float _z_interpolada= _posicion_anterior->_z * (1 -_i_interpolacion) + _posicion_actual->_z * _i_interpolacion;

    return Vector3(_x_interpolada, _y_interpolada, _z_interpolada);
}