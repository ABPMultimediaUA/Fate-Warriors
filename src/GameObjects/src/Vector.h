#ifndef VECTOR_H
#define VECTOR_H

struct Vector2;
struct Vector3;


struct Vector2{
	float _x;
	float _y;

	//Constructor
	Vector2(float _i_x, float _i_y);

	//Para floats
	
	Vector2& operator *=(const float _i_valor);
	Vector2& operator /=(const float _i_valor);
	Vector2& operator +=(const float _i_valor);
	Vector2& operator -=(const float _i_valor);
	
	
	//Para short
	Vector2& operator *=(const short _i_valor);
	Vector2& operator /=(const short _i_valor);
	Vector2& operator +=(const short _i_valor);
	Vector2& operator -=(const short _i_valor);

};

struct Vector3{
	float _x;
	float _y;
	float _z;

	//Constructor
	Vector3(float _i_x, float _i_y, float _i_z);

	//Para floats
	
	Vector3& operator *=(const float _i_valor);
	Vector3& operator /=(const float _i_valor);
	Vector3& operator +=(const float _i_valor);
	Vector3& operator -=(const float _i_valor);

	
	//Para short
	Vector3& operator *=(const short _i_valor);
	Vector3& operator /=(const short _i_valor);
	Vector3& operator +=(const short _i_valor);
	Vector3& operator -=(const short _i_valor);
};


//VECTOR 2D
	//Para floats
	
Vector2 operator *(Vector2 _i_vector, const float _i_valor);
Vector2 operator /(Vector2 _i_vector, const float _i_valor);
Vector2 operator +(Vector2 _i_vector, const float _i_valor);
Vector2 operator -(Vector2 _i_vector, const float _i_valor);


	//Para short
Vector2 operator *(Vector2 _i_vector, const short _i_valor);
Vector2 operator /(Vector2 _i_vector, const short _i_valor);
Vector2 operator +(Vector2 _i_vector, const short _i_valor);
Vector2 operator -(Vector2 _i_vector, const short _i_valor);



//VECTOR 3D
	//Para floats

Vector3 operator *(Vector3 _i_vector, const float _i_valor);
Vector3 operator /(Vector3 _i_vector, const float _i_valor);
Vector3 operator +(Vector3 _i_vector, const float _i_valor);
Vector3 operator -(Vector3 _i_vector, const float _i_valor);


	//Para short
Vector3 operator *(Vector3 _i_vector, const short _i_valor);
Vector3 operator /(Vector3 _i_vector, const short _i_valor);
Vector3 operator +(Vector3 _i_vector, const short _i_valor);
Vector3 operator -(Vector3 _i_vector, const short _i_valor);



#endif /* VECTOR_H */