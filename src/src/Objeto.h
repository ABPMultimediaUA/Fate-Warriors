#ifndef HEADERS_OBJETO_H_
#define HEADERS_OBJETO_H_
#include "Utilidades/Vector.h"
#include <cstdint>
enum NombreObjetos{

};

class Matcher;



class Objeto {
public:

	Objeto(short id, float _i_x, float _i_y, float _i_z);
	virtual ~Objeto();

	virtual void update() = 0;
	virtual void render() = 0;
	virtual float getX(){return _x;};
	virtual float getY(){return _y;};
	virtual float getZ(){return _z;};

	void 	setPosition(float _i_x, float _i_y, float _i_z);
	//float	getX();
	//float getY();
	//float getZ();
	void	setX(float _i_x);
	void	setY(float _i_y);
	void	setZ(float _i_z);
	void	set_borrar();
	bool 	get_borrar();
	Vector2	get_vector();
    void set_visible(bool visible);
    bool get_visible();
    short get_id();

protected:
	short 	_id;
	float 	_x;
	float 	_y;
	float 	_z;
	bool 	_borrar;
	Matcher* _matcher;
    bool _visible;
};

#endif /* HEADERS_OBJETO_H_ */
