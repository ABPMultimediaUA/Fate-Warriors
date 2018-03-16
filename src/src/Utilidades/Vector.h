#ifndef VECTOR_H_
#define VECTOR_H_

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

	//Operaciones 
	float Length();
    float LengthSq();
	Vector2 Perp();
	void Normalize();

    void Truncate(float num);
    void zero();   
    double Dot(const Vector2& v2)const;

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


//VECTOR 2D////////////////////////////////////////////////


	/*---------Operaciones matematicas---------*/

float Vector2DistanceSq(Vector2 v1, Vector2 v2);
float Vector2Distance( Vector2 v1,  Vector2 v2);
bool comprobar_colision_teniendo_tambien_radio(Vector2 v1, float radio1, Vector2 v2, float radio2);

	/*---------Operaciones elementales---------*/
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


//VECTOR 3D////////////////////////////////////////////////
	/*---------Operaciones elementales---------*/
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




#endif /* VECTOR_H_ */





