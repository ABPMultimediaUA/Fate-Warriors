#ifndef HEADERS_OBJETO_H_
#define HEADERS_OBJETO_H_
#include "Utilidades/Vector.h"
#include "Interfaz/EnumTiposBoundingBox.h"
#include "Interfaz/Objeto_Motor.h"

#include <cstdint>


class Motor;

enum NombreObjetos{

};


class Objeto {
public:

	Objeto(short id, float _i_x, float _i_y, float _i_z);
	virtual ~Objeto();

	virtual void update() = 0;
	virtual void render() = 0;
	float getX();
	float getY();
	float getZ();
	
	void setPositionXZ(float _i_x, float _i_z);
	void	setX(float _i_x);
	void	setY(float _i_y);
	void	setZ(float _i_z);
	void	haz_desaparecer();
	void	set_borrar();
	bool 	get_borrar();
	Vector2	get_vector();
    void set_visible(bool visible);
    bool get_visible();
    short get_id();

protected:
	short 	_id;
	Objeto_Motor * _objeto_motor;
	bool 	_borrar;
    bool _visible;
};

#endif /* HEADERS_OBJETO_H_ */
