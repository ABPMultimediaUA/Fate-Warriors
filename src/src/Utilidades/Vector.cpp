#include "Vector.h"
#include <math.h>
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




 /////////////////VECTOR 2D
 Vector2 operator+(Vector2 _i_vector, const Vector2 _i_vector2){
    Vector2 resultado(0,0);
    resultado._x=_i_vector._x + _i_vector2._x;
    resultado._y=_i_vector._y + _i_vector2._y;
    return resultado;
 }




float Vector2::Length() {
    return sqrt(_x * _x + _y * _y);
};
 
float Vector2::LengthSq() {
    return (_x * _x + _y * _y);
};

Vector2 Vector2::Perp(){
    return Vector2(-_y, _x);
};
 
void Vector2::Normalize() {
    float length = Length();
    if (length>0){
        _x = _x / length;
        _y = _y / length;
    }
};

void Vector2::Truncate(float num) {
    if (Length()>num){
        Normalize();
        (*this)=(*this) * num;
    }
};
 
void Vector2::zero() {
    _x=0.0f;
    _y=0.0f;
}
 

 float Vector2DistanceSq(Vector2 v1, Vector2 v2){
     float ySeparation = v2._y - v1._y;
     float xSeparation = v2._x - v1._x;
 
  return ySeparation*ySeparation + xSeparation*xSeparation;
}


float Vector2Distance( Vector2 v1,  Vector2 v2){
    float sepX = v2._x - v1._x;
    float sepY = v2._y - v1._y;
    return sqrt(sepX*sepX+ sepY*sepY);
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
    float Length();
    float LengthSq();

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

