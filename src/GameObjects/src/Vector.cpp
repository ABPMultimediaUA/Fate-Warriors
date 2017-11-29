#include "Vector.h"

//Para el vector 2D
Vector2::Vector2(float _i_x, float _i_y): _x(_i_x), _y(_i_y){}


//Operaciones con =

	////////FLOAT 
	
Vector2& Vector2::operator+=(const float _i_valor) {
    _x += _i_valor;
    _y += _i_valor;
    return *this;
};

Vector2& Vector2::operator*=(const float _i_valor) {
    _x *= _i_valor;
    _y *= _i_valor;
    return *this;
};

Vector2& Vector2::operator-=(const float _i_valor) {
    _x -= _i_valor;
    _y -= _i_valor;
    return *this;
};

Vector2& Vector2::operator/=(const float _i_valor) {
    _x /= _i_valor;
    _y /= _i_valor;
    return *this;
};

	////////SHORT
Vector2& Vector2::operator+=(const short _i_valor) {
    _x += _i_valor;
    _y += _i_valor;
    return *this;
};

Vector2& Vector2::operator*=(const short _i_valor) {
    _x *= _i_valor;
    _y *= _i_valor;
    return *this;
};

Vector2& Vector2::operator-=(const short _i_valor) {
	_x -= _i_valor;
    _y -= _i_valor;
    return *this;
};

Vector2& Vector2::operator/=(const short _i_valor) {
	_x /= _i_valor;
    _y /= _i_valor;
    return *this;
};


//Operaciones sin =

	/////////////////SHORT

Vector2 operator+(Vector2 _i_vector, const short _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x+_i_short;
    resultado._y=_i_vector._y+_i_short;
    return resultado;
 }


Vector2 operator-(Vector2 _i_vector, const short _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x-_i_short;
    resultado._y=_i_vector._y-_i_short;
    return resultado;
 }

Vector2 operator*(Vector2 _i_vector, const short _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x*_i_short;
    resultado._y=_i_vector._y*_i_short;
    return resultado;
 }

Vector2 operator/(Vector2 _i_vector, const short _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x/_i_short;
    resultado._y=_i_vector._y/_i_short;
    return resultado;
 }


	/////////////////FLOAT


Vector2 operator+(Vector2 _i_vector, const float _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x+_i_short;
    resultado._y=_i_vector._y+_i_short;
    return resultado;
 }


Vector2 operator-(Vector2 _i_vector, const float _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x-_i_short;
    resultado._y=_i_vector._y-_i_short;
    return resultado;
 }

Vector2 operator*(Vector2 _i_vector, const float _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x*_i_short;
    resultado._y=_i_vector._y*_i_short;
    return resultado;
 }

Vector2 operator/(Vector2 _i_vector, const float _i_short){
	Vector2 resultado(0,0);
    resultado._x=_i_vector._x/_i_short;
    resultado._y=_i_vector._y/_i_short;
    return resultado;
 }



 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Para el vector 3D
Vector3::Vector3(float _i_x, float _i_y, float _i_z): _x(_i_x), _y(_i_y), _z(_i_z){}


//Operaciones con =
	//Para floats
Vector3& Vector3::operator+=(const float _i_valor) {
    _x += _i_valor;
    _y += _i_valor;
    _z += _i_valor;
    return *this;
};

Vector3& Vector3::operator*=(const float _i_valor) {
    _x *= _i_valor;
    _y *= _i_valor;
    _z *= _i_valor;
    return *this;
};

Vector3& Vector3::operator-=(const float _i_valor) {
    _x -= _i_valor;
    _y -= _i_valor;
    _z -= _i_valor;
    return *this;
};

Vector3& Vector3::operator/=(const float _i_valor) {
    _x /= _i_valor;
    _y /= _i_valor;
    _z /= _i_valor;
    return *this;
};



	//Para shorts
Vector3& Vector3::operator+=(const short _i_valor) {
    _x += _i_valor;
    _y += _i_valor;
    _z += _i_valor;
    return *this;
};

Vector3& Vector3::operator*=(const short _i_valor) {
    _x *= _i_valor;
    _y *= _i_valor;
    _z *= _i_valor;
    return *this;
};

Vector3& Vector3::operator-=(const short _i_valor) {
	_x -= _i_valor;
    _y -= _i_valor;
    _z -= _i_valor;
    return *this;
};

Vector3& Vector3::operator/=(const short _i_valor) {
	_x /= _i_valor;
    _y /= _i_valor;
    _z /= _i_valor;
    return *this;
};



//Operaciones sin =

	/////////////////SHORT

Vector3 operator+(Vector3 _i_vector, const short _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x+_i_short;
    resultado._y=_i_vector._y+_i_short;
    resultado._z=_i_vector._z/_i_short;
    return resultado;
 }


Vector3 operator-(Vector3 _i_vector, const short _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x-_i_short;
    resultado._y=_i_vector._y-_i_short;
    resultado._z=_i_vector._z/_i_short;

    return resultado;
 }

Vector3 operator*(Vector3 _i_vector, const short _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x*_i_short;
    resultado._y=_i_vector._y*_i_short;
    resultado._z=_i_vector._z/_i_short;

    return resultado;
 }

Vector3 operator/(Vector3 _i_vector, const short _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x/_i_short;
    resultado._y=_i_vector._y/_i_short;
    resultado._z=_i_vector._z/_i_short;

    return resultado;
 }


	/////////////////FLOAT

Vector3 operator+(Vector3 _i_vector, const float _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x+_i_short;
    resultado._y=_i_vector._y+_i_short;
    resultado._z=_i_vector._z/_i_short;
    return resultado;
 }


Vector3 operator-(Vector3 _i_vector, const float _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x-_i_short;
    resultado._y=_i_vector._y-_i_short;
    resultado._z=_i_vector._z/_i_short;
    return resultado;
 }

Vector3 operator*(Vector3 _i_vector, const float _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x*_i_short;
    resultado._y=_i_vector._y*_i_short;
    resultado._z=_i_vector._z/_i_short;
    return resultado;
 }

Vector3 operator/(Vector3 _i_vector, const float _i_short){
	Vector3 resultado(0,0,0);
    resultado._x=_i_vector._x/_i_short;
    resultado._y=_i_vector._y/_i_short;
    resultado._z=_i_vector._z/_i_short;

    return resultado;
 }

