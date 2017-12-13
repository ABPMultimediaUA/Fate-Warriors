#ifndef HEADERS_OBJETO_H_
#define HEADERS_OBJETO_H_

enum NombreObjetos{

};

#include "Utilidades/Vector.h"

class Character;

class Objeto {
public:

	Objeto(short id, float _i_x, float _i_y, float _i_z);
	virtual ~Objeto();

	virtual void render() = 0;

	void 	setPosition(float _i_x, float _i_y, float _i_z);
	float	getX();
	float 	getY();
	float 	getZ();
	void	setX(float _i_x);
	void	setY(float _i_y);
	void	setZ(float _i_z);
	void	set_borrar();
	bool 	get_borrar();
	Vector2	get_vector();

protected:
	short 	_id;
	float 	_x;
	float 	_y;
	float 	_z;
	bool 	_borrar;

};

#endif /* HEADERS_OBJETO_H_ */